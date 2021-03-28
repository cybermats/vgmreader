#include <criterion/criterion.h>

#include "decode.h"


static unsigned char compressed[] =
  {
    0x1f, 0x8b, 0x08, 0x00,  0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x15, 0xc5,  0xc9, 0x11, 0x00, 0x10,
    0x14, 0x04, 0xd1, 0x6f,  0xdf, 0xc5, 0x20, 0x2a,
    0x29, 0x38, 0x09, 0x9e,  0x08, 0xb4, 0xa9, 0x7a,
    0xd3, 0x73, 0xed, 0xa1,  0xe4, 0x4f, 0x89, 0xe6,
    0x0d, 0x2c, 0x1c, 0x3c,  0x02, 0x22, 0x92, 0x9c,
    0x9b, 0x69, 0x41, 0x45,  0x43, 0xc7, 0x03, 0x64,
    0x1a, 0xe8, 0x81, 0x40,  0x00, 0x00, 0x00
  };

static unsigned char uncompressed[] =
  {
    0x56, 0x67, 0x6d, 0x20,  0x01, 0x00, 0x00, 0x00, // 0x00
    0x00, 0x00, 0x01, 0x00,  0x02, 0x00, 0x00, 0x00, // 0x08
    0x03, 0x00, 0x00, 0x00,  0x04, 0x00, 0x00, 0x00, // 0x10
    0x05, 0x00, 0x00, 0x00,  0x06, 0x00, 0x00, 0x00, // 0x18
    0x07, 0x00, 0x00, 0x00,  0x08, 0x00, 0x00, 0x00, // 0x20
    0x09, 0x00, 0xf1, 0xf2,  0x0a, 0x00, 0x00, 0x00, // 0x28
    0x0b, 0x00, 0x00, 0x00,  0x0c, 0x00, 0x00, 0x00, // 0x30
    0x0d, 0x00, 0x00, 0x00,  0x0e, 0x00, 0x00, 0x00 // 0x38
  };



Test(decoder, test_file_type_unknown)
{
  const unsigned char buffer[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  int ft = file_type(buffer, sizeof(buffer));
  cr_assert_eq(ft, VGM_FT_UNKNOWN);
}

Test(decoder, test_file_type_null)
{
  int ft = file_type(NULL, 0);
  cr_assert_eq(ft, VGM_FT_UNKNOWN);
}

Test(decoder, test_file_type_empty)
{
  const unsigned char buffer[] = "";
  int ft = file_type(buffer, 0);
  cr_assert_eq(ft, VGM_FT_UNKNOWN);
}

Test(decoder, test_file_type_short_1)
{
  const unsigned char buffer[] = "V";
  int ft = file_type(buffer, 1);
  cr_assert_eq(ft, VGM_FT_UNKNOWN);
}

Test(decoder, test_file_type_short_3)
{
  const unsigned char buffer[] = "Vgm";
  int ft = file_type(buffer, 3);
  cr_assert_eq(ft, VGM_FT_UNKNOWN);
}

Test(decoder, test_file_type_vgm)
{
  const unsigned char buffer[] = {
    'V', 'g', 'm', ' ',
    0x00, 0x00, 0x00, 0x00
  };
  int ft = file_type(buffer, sizeof(buffer));
  cr_assert_eq(ft, VGM_FT_VGM);
}

Test(decoder, test_file_type_vgz)
{
  const unsigned char buffer[] = {
    0x1f, 0x8b, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  int ft = file_type(buffer, sizeof(buffer));
  cr_assert_eq(ft, VGM_FT_VGZ);
}

Test(decoder, test_decompression)
{
  unsigned char *buffer;
  size_t size = decompress(&buffer, compressed, sizeof(compressed));
  cr_assert_eq(size, sizeof(uncompressed));
  int diff = bcmp(buffer, uncompressed, size);
  cr_assert_eq(diff, 0);
}

