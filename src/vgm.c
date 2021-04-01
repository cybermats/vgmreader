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
  if (vgm_get_attr(vgm, VGM_SN76489))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "sn76489", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2413))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2413", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2612))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2612", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2151))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2151", size);
    }
  if (vgm_get_attr(vgm, VGM_SEGA_PCM))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "segaPCM", size);
    }
  if (vgm_get_attr(vgm, VGM_RF5C68))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "rf5c68", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2203))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2203", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2608))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2608", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2610))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2610", size);
    }
  if (vgm_get_attr(vgm, VGM_YM3812))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym3812", size);
    }
  if (vgm_get_attr(vgm, VGM_YM3526))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym3526", size);
    }
  if (vgm_get_attr(vgm, VGM_Y8950))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "y8950", size);
    }
  if (vgm_get_attr(vgm, VGM_YMF262))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf262", size);
    }
  if (vgm_get_attr(vgm, VGM_YMF278B))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf278b", size);
    }
  if (vgm_get_attr(vgm, VGM_YMF271))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymf271", size);
    }
  if (vgm_get_attr(vgm, VGM_YMZ280B))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ymz280b", size);
    }
  if (vgm_get_attr(vgm, VGM_RF5C164))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "rf5c164", size);
    }
  if (vgm_get_attr(vgm, VGM_PWM))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "pwm", size);
    }
  if (vgm_get_attr(vgm, VGM_AY8910))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ay8910", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2203))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "ym2203", size);
    }
  if (vgm_get_attr(vgm, VGM_YM2608))
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


size_t
vgm_process(const Vgm *vgm, int offset, VgmCommand *command)
{
  assert(vgm);
  assert(vgm->buffer);
  assert(command);
  uint8_t c = vgm->buffer[offset];
  command->command = c;

  // No argument commands.
  if (c == 0x62 ||
      c == 0x63 ||
      c == 0x66)
    {
      command->data = NULL;
      return offset + 1;
    }

  if ((c >= 0x70) && (c < 0x90))
    {
      command->data = NULL;
      return offset + 1;
    }

  // Single byte argument commands.
  if (c == 0x4f ||
      c == 0x50)
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 2;
    }

  if ((c >= 0x51 &&
       c <= 0x61) ||
      (c >= 0xa0 &&
       c < 0xc0))
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 3;
    }
  
  return 0;
}
