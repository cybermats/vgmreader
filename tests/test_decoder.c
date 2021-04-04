#include <criterion/criterion.h>
#include <signal.h>

#include "decode.h"

static unsigned char compressed[]
    = { 0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x15,
        0xc5, 0xc9, 0x11, 0x00, 0x10, 0x14, 0x04, 0xd1, 0x6f, 0xdf, 0xc5,
        0x20, 0x2a, 0x29, 0x38, 0x09, 0x9e, 0x08, 0xb4, 0xa9, 0x7a, 0xd3,
        0x73, 0xed, 0xa1, 0xe4, 0x4f, 0x89, 0xe6, 0x0d, 0x2c, 0x1c, 0x3c,
        0x02, 0x22, 0x92, 0x9c, 0x9b, 0x69, 0x41, 0x45, 0x43, 0xc7, 0x03,
        0x64, 0x1a, 0xe8, 0x81, 0x40, 0x00, 0x00, 0x00 };

static unsigned char uncompressed[] = {
  0x56, 0x67, 0x6d, 0x20, 0x01, 0x00, 0x00, 0x00, // 0x00
  0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, // 0x08
  0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // 0x10
  0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, // 0x18
  0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // 0x20
  0x09, 0x00, 0xf1, 0xf2, 0x0a, 0x00, 0x00, 0x00, // 0x28
  0x0b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, // 0x30
  0x0d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00  // 0x38
};

Test (decoder, test_null_file, .signal = SIGABRT) {
  size_t filesize = load_file(NULL, NULL);
  cr_assert_eq(filesize, 0);
}

Test (decoder, test_empty_buffer) {
  static uint8_t buffer[] = "";
  size_t size = sizeof(buffer);
  FILE *fp = fmemopen(buffer, size, "rb");
  cr_assert_not_null (fp);
  uint8_t *out_buffer = NULL;
  size_t filesize = load_file(fp, &out_buffer);
  cr_expect_eq (filesize, 0);
  cr_expect_null (out_buffer);
}

Test (decoder, test_non_vgm_buffer) {
  static uint8_t buffer[] = "abcdefghijklmnopqrstuvwxyz";
  size_t size = sizeof(buffer);
  FILE *fp = fmemopen(buffer, size, "rb");
  cr_assert_not_null (fp);
  uint8_t *out_buffer = NULL;
  size_t filesize = load_file(fp, &out_buffer);
  cr_expect_eq (filesize, 0);
  cr_expect_null (out_buffer);
}

Test (decoder, test_non_compressed_vgm) {
  size_t size = sizeof(uncompressed);
  FILE *fp = fmemopen(uncompressed, size, "rb");
  cr_assert_not_null (fp);
  uint8_t *out_buffer = NULL;
  size_t filesize = load_file(fp, &out_buffer);
  cr_expect_eq (filesize, size);
  int diff = bcmp (out_buffer, uncompressed, size);
  cr_expect_eq(diff, 0);
}

Test (decoder, test_compressed_vgm) {
  size_t size = sizeof(compressed);
  FILE *fp = fmemopen(compressed, size, "rb");
  cr_assert_not_null (fp);
  uint8_t *out_buffer = NULL;
  size_t filesize = load_file(fp, &out_buffer);
  cr_expect_eq (filesize, sizeof(uncompressed));
  int diff = bcmp (out_buffer, uncompressed, size);
  cr_expect_eq(diff, 0);
}
