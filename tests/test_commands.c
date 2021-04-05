#include <criterion/criterion.h>
#include <signal.h>
#include <stdint.h>

#include "decode.h"
#include "vgm.h"

static unsigned char master_buffer[] = {
    0x56, 0x67, 0x6d, 0x20, 0x01, 0x00, 0x00, 0x00,  // 0x00
    0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,  // 0x08
    0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,  // 0x10
    0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,  // 0x18
    0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,  // 0x20
    0x09, 0x00, 0xf1, 0xf2, 0x0a, 0x00, 0x00, 0x00,  // 0x28
    0x0b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,  // 0x30
    0x0d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,  // 0x38

    0x62, 0x63, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0x40 // No Args
    0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0x48 // Nibble Arg
    0x4f, 0xdd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0x50 // One byte Arg
    0x51, 0xaa, 0xdd, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0x58 // Two byte Arg
    0xc0, 0xbb, 0xaa, 0xdd, 0x00, 0x00, 0x00, 0x00,  // 0x60 // Three byte Arg.
    0xe0, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00,  // 0x68 // Four bytes
    0x67, 0x66, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,  // 0x70 // Data block
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 0x78
    0x1f, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00,
    0x00, 0x22, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x27,
    0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
    0x2a, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00,
    0x00, 0x2d, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00,

    0x2f, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00,
    0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00,
    0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00,
    0x3a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x3d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00,

};

static struct vgm_t *g_vgm = NULL;

void setup(void) {
  g_vgm = vgm_create(master_buffer, 0, sizeof(master_buffer));
}

void teardown(void) { vgm_free(g_vgm); }

TestSuite(command, .init = setup, .fini = teardown);

Test(command, test_bad_format, .signal = SIGABRT) {
  vgm_next_command(NULL, NULL, 0);
  cr_assert(0);
}

Test(command, test_zero_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x40;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 1);
  cr_expect_eq(command.command, 0x62);
  cr_expect_null(command.data);
}

Test(command, test_one_nibble_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x48;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 1);
  cr_expect_eq(command.command, 0x77);
  cr_expect_null(command.data);
}

Test(command, test_one_byte_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x50;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 2);
  cr_expect_eq(command.command, 0x4f);
  cr_expect_eq(command.data[0], 0xdd);
}

Test(command, test_two_byte_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x58;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 3);
  cr_expect_eq(command.command, 0x51);
  cr_expect_eq(command.data[0], 0xaa);
  cr_expect_eq(command.data[1], 0xdd);
}

Test(command, test_three_byte_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x60;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 4);
  cr_expect_eq(command.command, 0xc0);
  cr_expect_eq(command.data[0], 0xbb);
  cr_expect_eq(command.data[1], 0xaa);
  cr_expect_eq(command.data[2], 0xdd);
}

Test(command, test_four_byte_args) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x68;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 5);
  cr_expect_eq(command.command, 0xe0);
  cr_expect_eq(command.data[0], 0xaa);
  cr_expect_eq(command.data[1], 0xbb);
  cr_expect_eq(command.data[2], 0xcc);
  cr_expect_eq(command.data[3], 0xdd);
}

Test(command, test_data_block) {
  cr_assert_not_null(g_vgm);
  size_t offset = 0x70;
  struct vgm_command_t command;
  cr_expect_eq(vgm_next_command(&command, g_vgm, offset), offset + 8);
  cr_expect_eq(command.command, 0x67);
}
