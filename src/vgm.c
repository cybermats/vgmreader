#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vgm.h"


Vgm *vgm_create(const char *buffer, unsigned int offset, unsigned int size)
{
  const unsigned int header_size = size - offset;
  if (header_size < 256)
    return NULL;
  Vgm *vgm;
  vgm = malloc(sizeof(Vgm));
  vgm->eof_offset = parse_uint(buffer, offset + 4, size);
  vgm->version = parse_bcd(buffer, offset + 8, size);
  if (vgm->version < 100) {
    free(vgm);
    return NULL;
  }
  
  vgm->sn76489_clock = parse_uint(buffer, offset + 12, size);
  vgm->ym2413_clock = parse_uint(buffer, offset + 16, size);
  vgm->gd3_offset = parse_uint(buffer, offset + 20, size);
  vgm->total_num_samples = parse_uint(buffer, offset + 24, size);
  vgm->loop_offset = parse_uint(buffer, offset + 28, size);
  vgm->loop_num_samples = parse_uint(buffer, offset + 32, size);

  if (vgm->version >= 101) {
    vgm->rate = parse_uint(buffer, offset + 36, size);
  }

  if (vgm->version >= 110) {
    vgm->sn76489_feedback = parse_ushort(buffer, offset + 0x28, size);
    vgm->sn76489_shift_reg_width = parse_uchar(buffer, offset + 0x2a, size);
    vgm->ym2612_clock = parse_uint(buffer, offset + 0x2c, size);
    vgm->ym2151_clock = parse_uint(buffer, offset + 0x30, size);
  } else {
    vgm->sn76489_feedback = 9;
    vgm->sn76489_shift_reg_width = 16;
    vgm->ym2612_clock = vgm->ym2413_clock;
    vgm->ym2151_clock = vgm->ym2413_clock;
  }

  if (vgm->version >= 150) {
    vgm->data_offset = parse_uint(buffer, offset + 0x34, size);
  } else {
    vgm->data_offset = 0x40;
  }

  if (vgm->version >= 151) {
    vgm->sn76489_flags = parse_uchar(buffer, offset + 0x2b, size);
    vgm->sega_pcm_clock = parse_uint(buffer, offset + 0x38, size);
    vgm->sega_pcm_int_reg = parse_uint(buffer, offset + 0x3c, size);
    vgm->rf5c68_clock = parse_uint(buffer, offset + 0x40, size);
    vgm->ym2203_clock = parse_uint(buffer, offset + 0x44, size);
    vgm->ym2608_clock = parse_uint(buffer, offset + 0x48, size);
    vgm->ym2610_clock = parse_uint(buffer, offset + 0x4c, size);
    vgm->ym3812_clock = parse_uint(buffer, offset + 0x50, size);
    vgm->ym3526_clock = parse_uint(buffer, offset + 0x54, size);
    vgm->y8950_clock = parse_uint(buffer, offset + 0x58, size);
    vgm->ymf262_clock = parse_uint(buffer, offset + 0x5c, size);
    vgm->ymf278b_clock = parse_uint(buffer, offset + 0x60, size);
    vgm->ymf271_clock = parse_uint(buffer, offset + 0x64, size);
    vgm->ymz280b_clock = parse_uint(buffer, offset + 0x68, size);
    vgm->rf5c164_clock = parse_uint(buffer, offset + 0x6c, size);
    vgm->pwm_clock = parse_uint(buffer, offset + 0x70, size);
    vgm->ay8910_clock = parse_uint(buffer, offset + 0x74, size);
    vgm->ay8910_chip_type = parse_uchar(buffer, offset + 0x78, size);
    vgm->ay8910_flags = parse_uchar(buffer, offset + 0x79, size);
    vgm->ym2203_flags = parse_uchar(buffer, offset + 0x7a, size);
    vgm->ym2608_flags = parse_uchar(buffer, offset + 0x7b, size);
    vgm->loop_modifier = parse_uchar(buffer, offset + 0x7f, size);    
  } else {
    vgm->sn76489_flags = 0x00;
    vgm->sega_pcm_clock = 0x00;
    vgm->sega_pcm_int_reg = 0x00;
    vgm->rf5c68_clock = 0x00;
    vgm->ym2203_clock = 0x00;
    vgm->ym2608_clock = 0x00;
    vgm->ym2610_clock = 0x00;
    vgm->ym3812_clock = 0x00;
    vgm->ym3526_clock = 0x00;
    vgm->y8950_clock = 0x00;
    vgm->ymf262_clock = 0x00;
    vgm->ymf278b_clock = 0x00;
    vgm->ymf271_clock = 0x00;
    vgm->ymz280b_clock = 0x00;
    vgm->rf5c164_clock = 0x00;
    vgm->pwm_clock = 0x00;
    vgm->ay8910_clock = 0x00;
    vgm->ay8910_chip_type = 0x00;
    vgm->ay8910_flags = 0x00;
    vgm->ym2203_flags = 0x00;
    vgm->ym2608_flags = 0x00;
    vgm->loop_modifier = 0x00;    
  }
  
  return vgm;
}

void vgm_free(Vgm *vgm)
{
  free(vgm);
  return;
}

int vgm_validate_buffer(const char *buffer, unsigned int size)
{
  if (size < 4)
    return 0;
  if (strncmp(buffer, "Vgm ", 4) == 0)
    return 1;
  return 0;
}


unsigned int parse_uint(const char *buffer, unsigned int offset, unsigned int size)
{
  assert(buffer);
  union {
    char c[4];
    unsigned int v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset+1];
  im.c[2] = buffer[offset+2];
  im.c[3] = buffer[offset+3];
  return im.v;
}

unsigned int parse_ushort(const char *buffer, unsigned int offset, unsigned int size)
{
  assert(buffer);
  union {
    char c[2];
    unsigned short v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset+1];
  return im.v;
}

unsigned int parse_uchar(const char *buffer, unsigned int offset, unsigned int size)
{
  assert(buffer);
  return (unsigned char)buffer[offset];
}

unsigned int parse_bcd(const char *buffer, unsigned int offset, unsigned int size)
{
  assert(buffer);
  unsigned int value = 0;
  for (int i = offset; i < size && i < offset + 4; ++i) {
    value *= 10;
    value += buffer[i] >> 4;
    value *= 10;
    value += buffer[i] % 16;
  }
  return value;
}
