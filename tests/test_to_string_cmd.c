#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <stdint.h>
#include <stdlib.h>

#include "vgm.h"

TestSuite(stringify);

struct to_string_param_t {
  uint8_t cmd;
  enum cmd_type_t cmd_type;
  enum action_type_t action;
  uint8_t data[32];
  size_t data_size;
  char expected[128];
};

ParameterizedTestParameters(stringify, test_to_string) {
  static struct to_string_param_t params[] = {
      // No args
      {0x62,
       cmd_type_none,
       action_type_wait,
       {0x00},
       1,
       "[Wait] One frame (60Hz)"},
      {0x63,
       cmd_type_none,
       action_type_wait,
       {0x00},
       1,
       "[Wait] One frame (50Hz)"},
      {0x66,
       cmd_type_none,
       action_type_eos,
       {0x00},
       1,
       "[EOS] End of sound data"},
      // One Nibble Arg
      {0x70,
       cmd_type_nibble_inc,
       action_type_wait,
       {0x00},
       1,
       "[Wait] Samples: 1"},
      {0x77,
       cmd_type_nibble_inc,
       action_type_wait,
       {0x00},
       1,
       "[Wait] Samples: 8"},
      {0x7f,
       cmd_type_nibble_inc,
       action_type_wait,
       {0x00},
       1,
       "[Wait] Samples: 16"},
      {0x80,
       cmd_type_nibble,
       action_type_ym2612,
       {0x00},
       1,
       "[YM2612] [0x2a]:0 <- data bank, then wait 0 samples"},
      {0x87,
       cmd_type_nibble,
       action_type_ym2612,
       {0x00},
       1,
       "[YM2612] [0x2a]:0 <- data bank, then wait 7 samples"},
      {0x8f,
       cmd_type_nibble,
       action_type_ym2612,
       {0x00},
       1,
       "[YM2612] [0x2a]:0 <- data bank, then wait 15 samples"},
      // One Byte Arg
      {0x4f,
       cmd_type_byte,
       action_type_game_gear_pcm,
       {0x01},
       1,
       "[Game Gear PCM] :6 <- 0x01"},
      {0x50, cmd_type_byte, action_type_psg, {0x01}, 1, "[PSG] : <- 0x01"},
      {0x30, cmd_type_byte, action_type_reserved, {0x01}, 1, "[Reserved]"},
      {0x37, cmd_type_byte, action_type_reserved, {0x01}, 1, "[Reserved]"},
      {0x3f, cmd_type_byte, action_type_reserved, {0x01}, 1, "[Reserved]"},
      // Two byte args
      {0x54,
       cmd_type_byte_byte,
       action_type_ym2151,
       {0x01, 0x02},
       2,
       "[YM2151] [0x01] <- 0x02"},
      {0x67,
       cmd_type_byte_byte,
       action_type_data_block,
       {0xff, 0x01, 0x00, 0x00, 0x00, 0xff},
       6,
       "[Data Block] Data Type 0xff, Size 0x01"},
  };
  size_t nb_params = sizeof(params) / sizeof(*params);
  return cr_make_param_array(struct to_string_param_t, params, nb_params);
}

ParameterizedTest(struct to_string_param_t *params, stringify, test_to_string) {
  struct vgm_command_t cmd = {params->cmd, params->cmd_type, params->action,
                              params->data, params->data_size};
  char str[512];
  int actual_ret = vgm_cmd_to_string(str, sizeof str, &cmd);
  cr_assert_eq(actual_ret, 0);
  cr_expect_str_eq(str, params->expected);
}
