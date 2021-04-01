#include <criterion/criterion.h>

#include "vgm.h"

static unsigned char master_buffer[] = {
  0x56, 0x67, 0x6d, 0x20, 0x01, 0x00, 0x00, 0x00, // 0x00
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // 0x08
  0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, // 0x10
  0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, // 0x18
  0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // 0x20
  0x09, 0x00, 0xf1, 0xf2, 0x0a, 0x00, 0x00, 0x00, // 0x28
  0x0b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, // 0x30
  0x0d, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, // 0x38

  0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, // 0x40
  0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, // 0x48
  0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, // 0x50
  0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, // 0x58
  0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, // 0x60
  0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, // 0x68
  0x1b, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, // 0x70
  0x1d, 0xf3, 0xf4, 0xf5, 0x1e, 0xf6, 0xf7, 0xf8, // 0x78

  0x1f, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x22,
  0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x25, 0x00,
  0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00,
  0x00, 0x29, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00,
  0x2c, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00,

  0x2f, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32,
  0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x35, 0x00,
  0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
  0x00, 0x39, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00,
};

void
copy_version (unsigned char *dst, const unsigned char *src,
              const unsigned char version[])
{
  memcpy (dst, src, 0x100);
  memcpy (&dst[0x08], version, 4);
}

Test (header, test_create_vgm_null)
{
  Vgm *vgm = vgm_create (NULL, 0, 0);
  cr_assert_null (vgm);
  vgm_free (vgm);
}

Test (header, test_create_vgm_too_small)
{
  char unsigned buffer[] = { 0x56, 0x67, 0x6d, 0x20 };
  Vgm *vgm = vgm_create (buffer, 0, 4);
  cr_assert_null (vgm);
  vgm_free (vgm);
}

Test (header, test_create_vgm_success)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x78, 0x56, 0x34, 0x12 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);
  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 12345678);
  vgm_free (vgm);
}

Test (header, test_create_vgm_v100)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x00, 0x01, 0x00, 0x00 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);
  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 100);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489), 2);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2413), 3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_GD3_OFFSET), 4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES), 5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_OFFSET), 6);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES), 7);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FEEDBACK), 9);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_SHIFT_REG_WIDTH), 0x10);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2612), vgm_get_attr(vgm, VGM_YM2413));
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2151), vgm_get_attr(vgm, VGM_YM2413));

  cr_expect_eq (vgm_get_attr(vgm, VGM_DATA_OFFSET), 0x40);

  vgm_free (vgm);
}

Test (header, test_create_vgm_v101)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x01, 0x01, 0x00, 0x00 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);

  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 101);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489), 2);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2413), 3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_GD3_OFFSET), 4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES), 5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_OFFSET), 6);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES), 7);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RATE), 8);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FEEDBACK), 9);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_SHIFT_REG_WIDTH), 0x10);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2612), vgm_get_attr(vgm, VGM_YM2413));
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2151), vgm_get_attr(vgm, VGM_YM2413));

  cr_expect_eq (vgm_get_attr(vgm, VGM_DATA_OFFSET), 0x40);

  vgm_free (vgm);
}

Test (header, test_create_vgm_v110)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x10, 0x01, 0x00, 0x00 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);

  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 110);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489), 2);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2413), 3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_GD3_OFFSET), 4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES), 5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_OFFSET), 6);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES), 7);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RATE), 8);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FEEDBACK), 9);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_SHIFT_REG_WIDTH), 0xf1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2612), 0x0a);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2151), 0x0b);

  cr_expect_eq (vgm_get_attr(vgm, VGM_DATA_OFFSET), 0x40);

  vgm_free (vgm);
}

Test (header, test_create_vgm_v150)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x50, 0x01, 0x00, 0x00 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);

  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 150);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489), 2);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2413), 3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_GD3_OFFSET), 4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES), 5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_OFFSET), 6);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES), 7);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RATE), 8);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FEEDBACK), 9);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_SHIFT_REG_WIDTH), 0xf1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2612), 0x0a);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2151), 0x0b);

  cr_expect_eq (vgm_get_attr(vgm, VGM_DATA_OFFSET), 0x0c);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FLAGS), 0x0);  
  cr_expect_eq (vgm_get_attr(vgm, VGM_SEGA_PCM), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SEGA_PCM_INTERFACE_REG), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RF5C68), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2203), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2608), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2610), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM3812), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM3526), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_Y8950), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF262), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF278B), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF271), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMZ280B), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RF5C164), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_PWM), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910_CHIP_TYPE), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910_FLAGS), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2203_FLAGS), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2608_FLAGS), 0x0);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_MODIFIER), 0x0);
  
  vgm_free (vgm);
}

Test (header, test_create_vgm_v151)
{
  unsigned char buffer[0x100];
  unsigned char version[] = { 0x51, 0x01, 0x00, 0x00 };
  copy_version (buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create (buffer, 0, sizeof (buffer));
  cr_assert_not_null (vgm);

  cr_expect_eq (vgm_get_attr(vgm, VGM_EOF), 1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_VERSION), 151);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489), 2);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2413), 3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_GD3_OFFSET), 4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES), 5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_OFFSET), 6);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES), 7);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RATE), 8);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FEEDBACK), 9);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_SHIFT_REG_WIDTH), 0xf1);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2612), 0x0a);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2151), 0x0b);

  cr_expect_eq (vgm_get_attr(vgm, VGM_DATA_OFFSET), 0x0c);

  cr_expect_eq (vgm_get_attr(vgm, VGM_SN76489_FLAGS), 0xf2);  
  cr_expect_eq (vgm_get_attr(vgm, VGM_SEGA_PCM), 0x0d);
  cr_expect_eq (vgm_get_attr(vgm, VGM_SEGA_PCM_INTERFACE_REG), 0x0e);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RF5C68), 0x0f);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2203), 0x10);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2608), 0x11);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2610), 0x12);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM3812), 0x13);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM3526), 0x14);
  cr_expect_eq (vgm_get_attr(vgm, VGM_Y8950), 0x15);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF262), 0x16);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF278B), 0x17);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMF271), 0x18);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YMZ280B), 0x19);
  cr_expect_eq (vgm_get_attr(vgm, VGM_RF5C164), 0x1a);
  cr_expect_eq (vgm_get_attr(vgm, VGM_PWM), 0x1b);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910), 0x1c);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910_CHIP_TYPE), 0x1d);
  cr_expect_eq (vgm_get_attr(vgm, VGM_AY8910_FLAGS), 0xf3);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2203_FLAGS), 0xf4);
  cr_expect_eq (vgm_get_attr(vgm, VGM_YM2608_FLAGS), 0xf5);
  cr_expect_eq (vgm_get_attr(vgm, VGM_LOOP_MODIFIER), 0xf8);

  vgm_free (vgm);
}
