#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>

#include "vgm.h"

static char membuffer[1024];

static FILE *g_mem_stream = NULL;

void
pc_setup (void)
{
  g_mem_stream = fmemopen (membuffer, sizeof (membuffer), "wb");
}

void
pc_teardown (void)
{
  fclose (g_mem_stream);
}

TestSuite (process_commands, .init = pc_setup, .fini = pc_teardown);

struct no_args_param
{
  uint8_t command;
  uint8_t data[128];
  size_t data_size;
  int ret_value;
  char expected[128];
};

ParameterizedTestParameters (process_commands, test_args)
{
  static struct no_args_param params[] = {
    // No args
    { 0x62, { 0x00 }, 1, 0, "[Wait] One frame (60Hz)\n" },
    { 0x63, { 0x00 }, 1, 0, "[Wait] One frame (50Hz)\n" },
    { 0x66, { 0x00 }, 1, 1, "[EOS] End of sound data\n" },
    // One Nibble Arg
    { 0x70, { 0x00 }, 1, 0, "[Wait] Samples: 1\n" },
    { 0x77, { 0x00 }, 1, 0, "[Wait] Samples: 8\n" },
    { 0x7f, { 0x00 }, 1, 0, "[Wait] Samples: 16\n" },
    { 0x80, { 0x00 }, 1, 0, "[YM2612] [0x2a]:0 <- data bank, then wait 0 samples\n" },
    { 0x87, { 0x00 }, 1, 0, "[YM2612] [0x2a]:0 <- data bank, then wait 7 samples\n" },
    { 0x8f, { 0x00 }, 1, 0, "[YM2612] [0x2a]:0 <- data bank, then wait 15 samples\n" },
    // One Byte Arg
    { 0x4f, { 0x01 }, 1, 0, "[Game Gear PCM] :6 <- 0x01\n" },
    { 0x50, { 0x01 }, 1, 0, "[PSG] <- 0x01\n" },
    { 0x30, { 0x01 }, 1, 0, "[reserved]\n" },
    { 0x37, { 0x01 }, 1, 0, "[reserved]\n" },
    { 0x3f, { 0x01 }, 1, 0, "[reserved]\n" },
    // Two byte args
    { 0x54, { 0x01, 0x02 }, 2, 0, "[YM2151] [0x01] <- 0x02\n" },
    { 0x67,
      { 0xff, 0x01, 0x00, 0x00, 0x00, 0xff },
      6,
      0,
      "[Data Block] Data Type 0xff, Size 0x01\n" },
  };
  size_t nb_params = sizeof (params) / sizeof (struct no_args_param);
  return cr_make_param_array (struct no_args_param, params, nb_params);
}

ParameterizedTest (struct no_args_param *params, process_commands, test_args)
{
  cr_assert_not_null (g_mem_stream);
  VgmCommand cmd = { params->command, params->data, params->data_size };
  int actual_ret = vgm_process_command (g_mem_stream, &cmd);
  cr_assert_eq (actual_ret, params->ret_value);
  fflush (g_mem_stream);
  cr_expect_str_eq (membuffer, params->expected);
}
