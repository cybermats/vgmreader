#include <criterion/criterion.h>

#include "vgm.h"

static unsigned char master_buffer[] =
  {
    0x56, 0x67, 0x6d, 0x20,  0x01, 0x00, 0x00, 0x00, // 0x00
    0x00, 0x00, 0x00, 0x00,  0x02, 0x00, 0x00, 0x00, // 0x08
    0x03, 0x00, 0x00, 0x00,  0x04, 0x00, 0x00, 0x00, // 0x10
    0x05, 0x00, 0x00, 0x00,  0x06, 0x00, 0x00, 0x00, // 0x18
    0x07, 0x00, 0x00, 0x00,  0x08, 0x00, 0x00, 0x00, // 0x20
    0x09, 0x00, 0xf1, 0xf2,  0x0a, 0x00, 0x00, 0x00, // 0x28
    0x0b, 0x00, 0x00, 0x00,  0x0c, 0x00, 0x00, 0x00, // 0x30
    0x0d, 0x00, 0x00, 0x00,  0x0e, 0x00, 0x00, 0x00, // 0x38
    
    0x0f, 0x00, 0x00, 0x00,  0x10, 0x00, 0x00, 0x00, // 0x40
    0x11, 0x00, 0x00, 0x00,  0x12, 0x00, 0x00, 0x00, // 0x48
    0x13, 0x00, 0x00, 0x00,  0x14, 0x00, 0x00, 0x00, // 0x50
    0x15, 0x00, 0x00, 0x00,  0x16, 0x00, 0x00, 0x00, // 0x58
    0x17, 0x00, 0x00, 0x00,  0x18, 0x00, 0x00, 0x00, // 0x60
    0x19, 0x00, 0x00, 0x00,  0x1a, 0x00, 0x00, 0x00, // 0x68
    0x1b, 0x00, 0x00, 0x00,  0x1c, 0x00, 0x00, 0x00, // 0x70
    0x1d, 0xf3, 0xf4, 0xf5,  0x1e, 0xf6, 0xf7, 0xf8, // 0x78
    
    0x1f, 0x00, 0x00, 0x00,  0x20, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00,  0x22, 0x00, 0x00, 0x00,
    0x23, 0x00, 0x00, 0x00,  0x24, 0x00, 0x00, 0x00,
    0x25, 0x00, 0x00, 0x00,  0x26, 0x00, 0x00, 0x00,
    0x27, 0x00, 0x00, 0x00,  0x28, 0x00, 0x00, 0x00,
    0x29, 0x00, 0x00, 0x00,  0x2a, 0x00, 0x00, 0x00,
    0x2b, 0x00, 0x00, 0x00,  0x2c, 0x00, 0x00, 0x00,
    0x2d, 0x00, 0x00, 0x00,  0x2e, 0x00, 0x00, 0x00,
    
    0x2f, 0x00, 0x00, 0x00,  0x30, 0x00, 0x00, 0x00,
    0x31, 0x00, 0x00, 0x00,  0x32, 0x00, 0x00, 0x00,
    0x33, 0x00, 0x00, 0x00,  0x34, 0x00, 0x00, 0x00,
    0x35, 0x00, 0x00, 0x00,  0x36, 0x00, 0x00, 0x00,
    0x37, 0x00, 0x00, 0x00,  0x38, 0x00, 0x00, 0x00,
    0x39, 0x00, 0x00, 0x00,  0x3a, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x00, 0x00,  0x3c, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x00, 0x00,  0x3e, 0x00, 0x00, 0x00,
  };


void copy_version(unsigned char *dst, const unsigned char *src, const unsigned char version[])
{
  memcpy(dst, src, 0x100);
  memcpy(&dst[0x08], version, 4);
}

Test(header, test_create_vgm_null)
{
  Vgm *vgm = vgm_create(NULL, 0, 0);
  cr_assert_null(vgm);
  vgm_free(vgm);
}


Test(header, test_create_vgm_too_small)
{
  char unsigned buffer[] = {0x56, 0x67, 0x6d, 0x20};
  Vgm *vgm = vgm_create(buffer, 0, 4);
  cr_assert_null(vgm);
  vgm_free(vgm);
}


Test(header, test_create_vgm_success)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x78, 0x56, 0x34, 0x12 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 12345678);
  vgm_free(vgm);
}


Test(header, test_create_vgm_v100)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x00, 0x01, 0x00, 0x00 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 100);
  cr_assert_eq(vgm->sn76489_clock, 2);
  cr_assert_eq(vgm->ym2413_clock, 3);
  cr_assert_eq(vgm->gd3_offset, 4);
  cr_assert_eq(vgm->total_num_samples, 5);
  cr_assert_eq(vgm->loop_offset, 6);
  cr_assert_eq(vgm->loop_num_samples, 7);
  
  cr_assert_eq(vgm->data_offset, 0x40);
  vgm_free(vgm);
}

  
Test(header, test_create_vgm_v101)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x01, 0x01, 0x00, 0x00 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 101);
  cr_assert_eq(vgm->sn76489_clock, 2);
  cr_assert_eq(vgm->ym2413_clock, 3);
  cr_assert_eq(vgm->gd3_offset, 4);
  cr_assert_eq(vgm->total_num_samples, 5);
  cr_assert_eq(vgm->loop_offset, 6);
  cr_assert_eq(vgm->loop_num_samples, 7);
  cr_assert_eq(vgm->rate, 8);

  cr_assert_eq(vgm->sn76489_feedback, 9);
  cr_assert_eq(vgm->sn76489_shift_reg_width, 0x10);
  cr_assert_eq(vgm->ym2612_clock, vgm->ym2413_clock);
  cr_assert_eq(vgm->ym2151_clock, vgm->ym2413_clock);

  cr_assert_eq(vgm->data_offset, 0x40);
  vgm_free(vgm);
}

  
Test(header, test_create_vgm_v110)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x10, 0x01, 0x00, 0x00 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 110);
  cr_assert_eq(vgm->sn76489_clock, 2);
  cr_assert_eq(vgm->ym2413_clock, 3);
  cr_assert_eq(vgm->gd3_offset, 4);
  cr_assert_eq(vgm->total_num_samples, 5);
  cr_assert_eq(vgm->loop_offset, 6);
  cr_assert_eq(vgm->loop_num_samples, 7);
  cr_assert_eq(vgm->rate, 8);
  
  cr_assert_eq(vgm->sn76489_feedback, 9);
  cr_assert_eq(vgm->sn76489_shift_reg_width, 0xf1);
  cr_assert_eq(vgm->ym2612_clock, 0x0a);
  cr_assert_eq(vgm->ym2151_clock, 0x0b);
  
  cr_assert_eq(vgm->data_offset, 0x40);
  vgm_free(vgm);
}


Test(header, test_create_vgm_v150)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x50, 0x01, 0x00, 0x00 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 150);
  cr_assert_eq(vgm->sn76489_clock, 2);
  cr_assert_eq(vgm->ym2413_clock, 3);
  cr_assert_eq(vgm->gd3_offset, 4);
  cr_assert_eq(vgm->total_num_samples, 5);
  cr_assert_eq(vgm->loop_offset, 6);
  cr_assert_eq(vgm->loop_num_samples, 7);
  cr_assert_eq(vgm->rate, 8);
  
  cr_assert_eq(vgm->sn76489_feedback, 9);
  cr_assert_eq(vgm->sn76489_shift_reg_width, 0xf1);
  cr_assert_eq(vgm->ym2612_clock, 0x0a);
  cr_assert_eq(vgm->ym2151_clock, 0x0b);

  cr_assert_eq(vgm->sn76489_flags, 0x0);
  cr_assert_eq(vgm->sega_pcm_clock, 0x0); // 0x38
  cr_assert_eq(vgm->sega_pcm_int_reg, 0x0); // 0x3c
  cr_assert_eq(vgm->rf5c68_clock, 0x0); // 0x40
  cr_assert_eq(vgm->ym2203_clock, 0x0); // 0x44
  cr_assert_eq(vgm->ym2608_clock, 0x0); // 0x48
  cr_assert_eq(vgm->ym2610_clock, 0x0); // 0x4c
  cr_assert_eq(vgm->ym3812_clock, 0x0); // 0x50
  cr_assert_eq(vgm->ym3526_clock, 0x0); // 0x54
  cr_assert_eq(vgm->y8950_clock, 0x0); // 0x58
  cr_assert_eq(vgm->ymf262_clock, 0x0); // 0x5c
  cr_assert_eq(vgm->ymf278b_clock, 0x0); // 0x60
  cr_assert_eq(vgm->ymf271_clock, 0x0); // 0x64
  cr_assert_eq(vgm->ymz280b_clock, 0x0); // 0x68
  cr_assert_eq(vgm->rf5c164_clock, 0x0); // 0x6c
  cr_assert_eq(vgm->pwm_clock, 0x0); // 0x70
  cr_assert_eq(vgm->ay8910_clock, 0x0); // 0x74
  cr_assert_eq(vgm->ay8910_chip_type, 0x0); // 0x78
  cr_assert_eq(vgm->ay8910_flags, 0x0); // 0x79
  cr_assert_eq(vgm->ym2203_flags, 0x0); // 0x7a
  cr_assert_eq(vgm->ym2608_flags, 0x0); // 0x7b
  cr_assert_eq(vgm->loop_modifier, 0x0); // 0x7f
  

  
  cr_assert_eq(vgm->data_offset, 0x0c);
  vgm_free(vgm);
}


Test(header, test_create_vgm_v151)
{
  unsigned char buffer[0x100];
  unsigned char version[] = {0x51, 0x01, 0x00, 0x00 };
  copy_version(buffer, master_buffer, version);

  Vgm *vgm;
  vgm = vgm_create(buffer, 0, sizeof(buffer));
  cr_assert_not_null(vgm);
  cr_assert_eq(vgm->eof_offset, 1);
  cr_assert_eq(vgm->version, 151);
  cr_assert_eq(vgm->sn76489_clock, 2);
  cr_assert_eq(vgm->ym2413_clock, 3);
  cr_assert_eq(vgm->gd3_offset, 4);
  cr_assert_eq(vgm->total_num_samples, 5);
  cr_assert_eq(vgm->loop_offset, 6);
  cr_assert_eq(vgm->loop_num_samples, 7);
  cr_assert_eq(vgm->rate, 8);
  
  cr_assert_eq(vgm->sn76489_feedback, 9);
  cr_assert_eq(vgm->sn76489_shift_reg_width, 0xf1);
  cr_assert_eq(vgm->ym2612_clock, 0x0a);
  cr_assert_eq(vgm->ym2151_clock, 0x0b);

  cr_assert_eq(vgm->sn76489_flags, 0xf2);
  cr_assert_eq(vgm->sega_pcm_clock, 0x0d); // 0x38
  cr_assert_eq(vgm->sega_pcm_int_reg, 0x0e); // 0x3c
  cr_assert_eq(vgm->rf5c68_clock, 0x0f); // 0x40
  cr_assert_eq(vgm->ym2203_clock, 0x10); // 0x44
  cr_assert_eq(vgm->ym2608_clock, 0x11); // 0x48
  cr_assert_eq(vgm->ym2610_clock, 0x12); // 0x4c
  cr_assert_eq(vgm->ym3812_clock, 0x13); // 0x50
  cr_assert_eq(vgm->ym3526_clock, 0x14); // 0x54
  cr_assert_eq(vgm->y8950_clock, 0x15); // 0x58
  cr_assert_eq(vgm->ymf262_clock, 0x16); // 0x5c
  cr_assert_eq(vgm->ymf278b_clock, 0x17); // 0x60
  cr_assert_eq(vgm->ymf271_clock, 0x18); // 0x64
  cr_assert_eq(vgm->ymz280b_clock, 0x19); // 0x68
  cr_assert_eq(vgm->rf5c164_clock, 0x1a); // 0x6c
  cr_assert_eq(vgm->pwm_clock, 0x1b); // 0x70
  cr_assert_eq(vgm->ay8910_clock, 0x1c); // 0x74
  cr_assert_eq(vgm->ay8910_chip_type, 0x1d); // 0x78
  cr_assert_eq(vgm->ay8910_flags, 0xf3); // 0x79
  cr_assert_eq(vgm->ym2203_flags, 0xf4); // 0x7a
  cr_assert_eq(vgm->ym2608_flags, 0xf5); // 0x7b
  cr_assert_eq(vgm->loop_modifier, 0xf8); // 0x7f
  
  cr_assert_eq(vgm->data_offset, 0x0c);

  vgm_free(vgm);
}


