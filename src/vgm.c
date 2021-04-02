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
  uint32_t attr = 0;
  char str[128];
  if ((attr = vgm_get_attr(vgm, VGM_SN76489)))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "sn76489", size);
      snprintf(str, sizeof(str), "sn76489(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2413)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2413(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2612)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2612(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2151)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2151(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_SEGA_PCM)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "segaPCM(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_RF5C68)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "rf5c68(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2203)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2203(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2608)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2608(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2610)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2610(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM3812)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym3812(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM3526)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym3526(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_Y8950)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "y8950(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YMF262)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ymf262(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YMF278B)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ymf278b(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YMF271)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ymf271(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YMZ280B)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ymz280b(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_RF5C164)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "rf5c164(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_PWM)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "pwm(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_AY8910)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ay8910(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2203)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2203(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr(vgm, VGM_YM2608)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf(str, sizeof(str), "ym2608(%d)", attr);
      strncat (dst, str, size);
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
vgm_next_command(const Vgm *vgm, int offset, VgmCommand *command)
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

  // Nibble argument
  if ((c >= 0x70) && (c < 0x90))
    {
      command->data = NULL;
      return offset + 1;
    }

  // Single byte argument commands.
  if ((c >= 0x30 &&
       c <= 0x3f) ||
      (c == 0x4f ||
       c == 0x50))
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 2;
    }

  // Two byte argument
  if ((c >= 0x51 &&
       c <= 0x61) ||
      (c >= 0xa0 &&
       c < 0xc0))
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 3;
    }

  // Three byte argument
  if ((c >= 0xc0 &&
       c <= 0xd6) ||
      (c >= 0xc9 &&
       c <= 0xcf) ||
      (c >= 0xd7 &&
       c <= 0xdf))
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 4;
    }

  // Four byte argument
  if (c >= 0xe0 &&
       c <= 0xff)
    {
      command->data = vgm->buffer + offset + 1;
      return offset + 5;
    }

  // Data block
  if (c == 0x67)
    {
      command->data = vgm->buffer + offset + 7;
      uint32_t data_size = parse_uint(vgm->buffer, offset + 3, vgm->size);
      command->size = vgm->size - (offset + 7);
      return offset + 7 + data_size;
    }

  return 0;
}

int vgm_process_command(FILE *fp, VgmCommand *command)
{
  if (command->command == 0x62)
    {
      fprintf (fp, "[Wait] One frame (60Hz)\n");
      return 0;
    }
  if (command->command == 0x63)
    {
      fprintf (fp, "[Wait] One frame (50Hz)\n");
      return 0;
    }
  if (command->command == 0x66)
    {
      fprintf (fp, "End of sound data\n");
      return 1;
    }
  if ((command->command & 0xf0) == 0x70)
    {
      fprintf( fp, "[Wait] Samples: %d\n", (command->command &0x0f)+1);
      return 0;
    }
  if ((command->command & 0xf0) == 0x80)
    {
      fprintf( fp, "[YM2612] port 0 address 2A, wait samples: %d\n", (command->command &0x0f));
      return 0;
    }
  if (command->command == 0x4f)
    {
      fprintf (fp, "[Game Gear PCM] Write %#04x to port 0x06\n",
               command->data[0]);
      return 0;
    }
  if (command->command == 0x50)
    {
      fprintf (fp, "[PSG] Write %#04x\n",
               command->data[0]);
      return 0;
    }
  if (command->command >= 0x30 &&
      command->command <= 0x3f)
    {
      fprintf (fp, "[reserved]\n");
      return 0;
    }
  if (command->command == 0x54)
    {
      uint8_t data = command->data[1];
      uint8_t reg = command->data[0];
      fprintf (fp, "[YM2151] Write %#04x to reg %#04x", data,reg);
      switch(reg)
	{
	case 0x01:
	  fprintf(fp, ", (TEST & LFO RESET)");
	  break;
	case 0x08:
	  fprintf(fp, ", (KEY ON)");
	  break;
	case 0x0f:
	  fprintf(fp, ", (NOISE ENABLE, NOISE FREQUENCY)");
	  break;
	case 0x11:
	  fprintf(fp, ", (CLOCK A1)");
	  break;
	case 0x12:
	  fprintf(fp, ", (CLOCK A2)");
	  break;
	case 0x13:
	  fprintf(fp, ", (CLOCK B)");
	  break;
	case 0x14:
	  fprintf(fp, ", (CLOCK FUNCTIONS)");
	  break;
	case 0x18:
	  fprintf(fp, ", (LOW FREQUENCY)");
	  break;
	case 0x19:
	  fprintf(fp, ", (PHASE AND AMP MODULATION)");
	  break;
	case 0x1b:
	  fprintf(fp, ", (CONTROL OUTPUT & WAVE FORM SELECT)");
	  break;
	case 0x20:
	  fprintf(fp, ", (CHANNEL CONTROL)");
	  break;
	};
      if (reg >= 0x28 && reg < 0x30)
	  fprintf(fp, ", (KEY CODE)");
      if (reg >= 0x30 && reg < 0x38)
	  fprintf(fp, ", (KEY FRACTION)");
      if (reg >= 0x38 && reg < 0x40)
	  fprintf(fp, ", (PHASE & AMP MODULATION SENS)");
      if (reg >= 0x40 && reg < 0x60)
	  fprintf(fp, ", (DETUNE & PHASE MULTIPLY)");
      if (reg >= 0x60 && reg < 0x80)
	  fprintf(fp, ", (TOTAL LEVEL)");
      if (reg >= 0x80 && reg < 0xa0)
	  fprintf(fp, ", (EG ATTACK)");
      if (reg >= 0xa0 && reg < 0xc0)
	  fprintf(fp, ", (EG DELAY 1)");
      if (reg >= 0xc0 && reg < 0xe0)
	  fprintf(fp, ", (EG DELAY 2)");
      if (reg >= 0xe0)
	  fprintf(fp, ", (EG DECAY LEVEL, RELEASE RATE)");
      fprintf(fp, "\n");
      return 0;
    }

  if (command->command == 0x67)
    {
      uint8_t data_type = parse_uchar(command->data, 0, command->size);
      uint32_t data_size = parse_uint(command->data, 1, command->size);
      fprintf (fp, "[Data Block] Data Type %#04x, Size %#04x\n", data_type, data_size);
      return 0;
    }
  return -1;
}
