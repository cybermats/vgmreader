#include "vgm.h"
#include "vgm_helper.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

Vgm *
vgm_create (const unsigned char *buffer, int offset, size_t size)
{
  const unsigned int header_size = size - offset;
  if (header_size < 256)
    return NULL;
  Vgm *vgm;
  vgm = malloc (sizeof (Vgm));
  vgm->buffer = buffer;
  vgm->size = size;

  vgm->eof_offset = parse_uint (buffer, offset + 4, size);
  vgm->version = parse_bcd (buffer, offset + 8, size);
  if (vgm->version < 100)
    {
      free (vgm);
      return NULL;
    }

  vgm->sn76489_clock = parse_uint (buffer, offset + 12, size);
  vgm->ym2413_clock = parse_uint (buffer, offset + 16, size);
  vgm->gd3_offset = parse_uint (buffer, offset + 20, size);
  vgm->total_num_samples = parse_uint (buffer, offset + 24, size);
  vgm->loop_offset = parse_uint (buffer, offset + 28, size);
  vgm->loop_num_samples = parse_uint (buffer, offset + 32, size);

  if (vgm->version >= 101)
    {
      vgm->rate = parse_uint (buffer, offset + 36, size);
    }

  if (vgm->version >= 110)
    {
      vgm->sn76489_feedback = parse_ushort (buffer, offset + 0x28, size);
      vgm->sn76489_shift_reg_width = parse_uchar (buffer, offset + 0x2a, size);
      vgm->ym2612_clock = parse_uint (buffer, offset + 0x2c, size);
      vgm->ym2151_clock = parse_uint (buffer, offset + 0x30, size);
    }
  else
    {
      vgm->sn76489_feedback = 9;
      vgm->sn76489_shift_reg_width = 16;
      vgm->ym2612_clock = vgm->ym2413_clock;
      vgm->ym2151_clock = vgm->ym2413_clock;
    }

  if (vgm->version >= 150)
    {
      vgm->data_offset = parse_uint (buffer, offset + 0x34, size);
    }
  else
    {
      vgm->data_offset = 0x40;
    }

  if (vgm->version >= 151)
    {
      vgm->sn76489_flags = parse_uchar (buffer, offset + 0x2b, size);
      vgm->sega_pcm_clock = parse_uint (buffer, offset + 0x38, size);
      vgm->sega_pcm_int_reg = parse_uint (buffer, offset + 0x3c, size);
      vgm->rf5c68_clock = parse_uint (buffer, offset + 0x40, size);
      vgm->ym2203_clock = parse_uint (buffer, offset + 0x44, size);
      vgm->ym2608_clock = parse_uint (buffer, offset + 0x48, size);
      vgm->ym2610_clock = parse_uint (buffer, offset + 0x4c, size);
      vgm->ym3812_clock = parse_uint (buffer, offset + 0x50, size);
      vgm->ym3526_clock = parse_uint (buffer, offset + 0x54, size);
      vgm->y8950_clock = parse_uint (buffer, offset + 0x58, size);
      vgm->ymf262_clock = parse_uint (buffer, offset + 0x5c, size);
      vgm->ymf278b_clock = parse_uint (buffer, offset + 0x60, size);
      vgm->ymf271_clock = parse_uint (buffer, offset + 0x64, size);
      vgm->ymz280b_clock = parse_uint (buffer, offset + 0x68, size);
      vgm->rf5c164_clock = parse_uint (buffer, offset + 0x6c, size);
      vgm->pwm_clock = parse_uint (buffer, offset + 0x70, size);
      vgm->ay8910_clock = parse_uint (buffer, offset + 0x74, size);
      vgm->ay8910_chip_type = parse_uchar (buffer, offset + 0x78, size);
      vgm->ay8910_flags = parse_uchar (buffer, offset + 0x79, size);
      vgm->ym2203_flags = parse_uchar (buffer, offset + 0x7a, size);
      vgm->ym2608_flags = parse_uchar (buffer, offset + 0x7b, size);
      vgm->loop_modifier = parse_uchar (buffer, offset + 0x7f, size);
    }
  else
    {
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

void
vgm_free (Vgm *vgm)
{
  free (vgm);
  return;
}

size_t
vgm_get_tags (const Vgm *vgm, char *dst, size_t size)
{
  int count = 0;
  if (vgm->sn76489_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "sn76489", size);
    }
  if (vgm->ym2413_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2413", size);
    }
  if (vgm->ym2612_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2612", size);
    }
  if (vgm->ym2151_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2151", size);
    }
  if (vgm->sega_pcm_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "segaPCM", size);
    }
  if (vgm->rf5c68_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "rf5c68", size);
    }
  if (vgm->ym2203_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2203", size);
    }
  if (vgm->ym2608_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2608", size);
    }
  if (vgm->ym2610_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2610", size);
    }
  if (vgm->ym3812_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym3812", size);
    }
  if (vgm->ym3526_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym3526", size);
    }
  if (vgm->y8950_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "y8950", size);
    }
  if (vgm->ymf262_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf262", size);
    }
  if (vgm->ymf278b_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf278b", size);
    }
  if (vgm->ymf271_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf271", size);
    }
  if (vgm->ymz280b_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymz280b", size);
    }
  if (vgm->rf5c164_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "rf5c164", size);
    }
  if (vgm->pwm_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "pwm", size);
    }
  if (vgm->ay8910_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ay8910", size);
    }
  if (vgm->ym2203_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2203", size);
    }
  if (vgm->ym2608_clock)
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2608", size);
    }
  return 0;
}

unsigned int
vgm_get_attr (const Vgm *vgm, int attribute)
{
  unsigned int version = parse_bcd (vgm->buffer, VGM_VERSION, vgm->size);
  if (attribute == VGM_VERSION)
    {
      return version;
    }

  if (version < 101)
    {
      if (attribute == VGM_RATE)
        return 0;
    }
  if (version < 110)
    {
      if (attribute == VGM_SN76489_FEEDBACK)
        return 0x09;
      if (attribute == VGM_SN76489_SHIFT_REG_WIDTH)
        return 0x10;
      if (attribute == VGM_YM2612 || attribute == VGM_YM2151)
        attribute = VGM_YM2413;
    }
  if (version < 150)
    {
      if (attribute == VGM_DATA_OFFSET)
        return 0x40;
    }
  if (version < 151)
    {
      if (attribute == VGM_SN76489_FLAGS || attribute == VGM_SEGA_PCM
          || attribute == VGM_SEGA_PCM_INTERFACE_REG || attribute == VGM_RF5C68
          || attribute == VGM_YM2203 || attribute == VGM_YM2608
          || attribute == VGM_YM2610 || attribute == VGM_YM3812
          || attribute == VGM_YM3526 || attribute == VGM_Y8950
          || attribute == VGM_YMF262 || attribute == VGM_YMF278B
          || attribute == VGM_YMF271 || attribute == VGM_YMZ280B
          || attribute == VGM_RF5C164 || attribute == VGM_PWM
          || attribute == VGM_AY8910 || attribute == VGM_AY8910_CHIP_TYPE
          || attribute == VGM_AY8910_FLAGS || attribute == VGM_YM2203_FLAGS
          || attribute == VGM_YM2608_FLAGS || attribute == VGM_LOOP_MODIFIER)
        return 0x0;
    }

  switch (attribute)
    {
    case VGM_SN76489_FEEDBACK:
      return parse_ushort (vgm->buffer, attribute, vgm->size);
    case VGM_SN76489_SHIFT_REG_WIDTH:
    case VGM_AY8910_CHIP_TYPE:
    case VGM_AY8910_FLAGS:
    case VGM_YM2203_FLAGS:
    case VGM_YM2608_FLAGS:
    case VGM_SN76489_FLAGS:
    case VGM_LOOP_MODIFIER:
      return parse_uchar (vgm->buffer, attribute, vgm->size);
    case VGM_VERSION:
      return parse_bcd (vgm->buffer, attribute, vgm->size);
    default:
      return parse_uint (vgm->buffer, attribute, vgm->size);
    }
}

int
vgm_validate_buffer (const unsigned char *buffer, size_t size)
{
  if (size < 4)
    return 0;
  if (strncmp ((const char *)buffer, "Vgm ", 4) == 0)
    return 1;
  return 0;
}
