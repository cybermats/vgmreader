#include "vgm.h"
#include "vgm_helper.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

Vgm *
vgm_create (const unsigned char *buffer, size_t offset, size_t size)
{
  const size_t header_size = size - offset;
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
  if ((attr = vgm_get_attr (vgm, VGM_SN76489)))
    {
      if (count++)
        strncat (dst, ", ", size);
      strncat (dst, "sn76489", size);
      snprintf (str, sizeof (str), "sn76489(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2413)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2413(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2612)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2612(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2151)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2151(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_SEGA_PCM)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "segaPCM(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_RF5C68)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "rf5c68(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2203)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2203(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2608)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2608(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2610)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2610(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM3812)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym3812(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM3526)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym3526(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_Y8950)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "y8950(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YMF262)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ymf262(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YMF278B)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ymf278b(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YMF271)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ymf271(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YMZ280B)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ymz280b(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_RF5C164)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "rf5c164(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_PWM)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "pwm(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_AY8910)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ay8910(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2203)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2203(%d)", attr);
      strncat (dst, str, size);
    }
  if ((attr = vgm_get_attr (vgm, VGM_YM2608)))
    {
      if ((count++))
        strncat (dst, ", ", size);
      snprintf (str, sizeof (str), "ym2608(%d)", attr);
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

enum cmd_type_t
  {
    cmd_type_none,
    cmd_type_nibble,
    cmd_type_byte,
    cmd_type_byte_byte,
    cmd_type_short,
    cmd_type_short_byte,
    cmd_type_byte_byte_byte,
    cmd_type_short_short,
    cmd_type_int,
    cmd_type_data_block,
  };

enum action_type_t
  {
    action_type_none,
    action_type_wait,
    action_type_game_gear_pcm,
    action_type_psg,
    action_type_ym2413,
    action_type_ym2612,
    action_type_ym2151,
    action_type_ym2203,
    action_type_ym2608,
    action_type_ym2610,
    action_type_ym3812,
    action_type_ym3526,
    action_type_y8950,
    action_type_ymz280b,
    action_type_ymf262,
    action_type_reserved,
    action_type_data_block,
    action_type_eos,
    action_type_sega_pcm,
    action_type_c352,
  };

struct command_info_t
{
  uint8_t cmd;
  enum cmd_type_t cmd_type;
  enum action_type_t action_type;
  char short_desc[128];
};

struct command_info_t command_info[] =
  {
    { 0x30, cmd_type_byte, action_type_reserved, "[reserved]" },
    { 0x40, cmd_type_byte_byte, action_type_reserved, "[reserved]" },
    
    { 0x4f, cmd_type_byte, action_type_game_gear_pcm, "[Game Gear PCM] :6 <- %#04x" },
    { 0x50, cmd_type_byte, action_type_psg, "[PSG] <- %#04x" },

    { 0x51, cmd_type_byte_byte, action_type_ym2413, "[%#04x] <- %#04x" },
    { 0x52, cmd_type_byte_byte, action_type_ym2612, "[%#04x]:0 <- %#04x" },
    { 0x53, cmd_type_byte_byte, action_type_ym2612, "[%#04x]:1 <- %#04x" },
    { 0x54, cmd_type_byte_byte, action_type_ym2151, "[YM2151] [%#04x] <- %#04x" },
    { 0x55, cmd_type_byte_byte, action_type_ym2203, "[%#04x] <- %#04x" },
    { 0x56, cmd_type_byte_byte, action_type_ym2608, "[%#04x]:0 <- %#04x" },
    { 0x57, cmd_type_byte_byte, action_type_ym2608, "[%#04x]:1 <- %#04x" },
    { 0x58, cmd_type_byte_byte, action_type_ym2610, "[%#04x]:0 <- %#04x" },
    { 0x59, cmd_type_byte_byte, action_type_ym2610, "[%#04x]:1 <- %#04x" },
    { 0x5a, cmd_type_byte_byte, action_type_ym3812, "[%#04x] <- %#04x" },
    { 0x5b, cmd_type_byte_byte, action_type_ym3526, "[%#04x] <- %#04x" },
    { 0x5c, cmd_type_byte_byte, action_type_y8950, "[%#04x] <- %#04x" },
    { 0x5d, cmd_type_byte_byte, action_type_ymz280b, "[%#04x] <- %#04x" },
    { 0x5e, cmd_type_byte_byte, action_type_ymf262, "[%#04x]:0 <- %#04x" },
    { 0x5f, cmd_type_byte_byte, action_type_ymf262, "[%#04x]:1 <- %#04x" },

    { 0x61, cmd_type_short, action_type_wait, "[Wait] Samples: %d" },
    { 0x62, cmd_type_none, action_type_wait, "[Wait] One frame (60Hz)" },
    { 0x63, cmd_type_none, action_type_wait, "[Wait] One frame (50Hz)" },

    { 0x66, cmd_type_none, action_type_eos, "[EOS] End of sound data" },

    { 0x67, cmd_type_data_block, action_type_data_block, "[Data Block] Data Type %#04x, Size %#04x" },

    // TODO: Fix nibble+1 for Wait
    { 0x70, cmd_type_nibble, action_type_wait, "[Wait] Samples: %d" },

    { 0x80, cmd_type_nibble, action_type_ym2612, "[YM2612] [0x2a]:0 <- data bank, then wait %d samples" },

    { 0xa1, cmd_type_byte_byte, action_type_reserved, "[reserved]" },

    
    { 0xc0, cmd_type_short_byte, action_type_sega_pcm, "[%#06x] <- %#04x" },

    { 0xc9, cmd_type_byte_byte_byte, action_type_reserved, "[reserved]" },
    { 0xd7, cmd_type_byte_byte_byte, action_type_reserved, "[reserved]" },

    
    { 0xe0, cmd_type_int, action_type_ym2612, "Seek to offset [%#010x] in PCM Data bank" },
    { 0xe1, cmd_type_short_short, action_type_c352, "[%#06x] <- %#06x" },

    { 0xe2, cmd_type_int, action_type_reserved, "reserved" },
    
  };

static int command_info_compare(const void *key, const void *member)
{
  int16_t k = *((uint8_t*)key);
  int16_t m = ((struct command_info_t*)member)->cmd;
  return k - m;
}

static uint8_t reduce_command(uint8_t cmd) {
  if ((0x30 <= cmd && 0x4f > cmd) ||
      (0x70 <= cmd && 0x90 > cmd))
    return cmd & 0xf0;
  if (0xa1 <= cmd && 0xb0 > cmd)
    return 0xa1;
  if (0xc9 <= cmd && 0xd0 > cmd)
    return 0xc9;
  if (0xd7 <= cmd && 0xe0 > cmd)
    return 0xd7;
  if (0xe2 <= cmd)
    return 0xe2;
  return cmd;
}


size_t
vgm_next_command (const Vgm *vgm, size_t offset, VgmCommand *command)
{
  assert (vgm);
  assert (vgm->buffer);
  assert (command);
  uint8_t c = vgm->buffer[offset];
  command->command = c;
  uint8_t lookup_cmd = reduce_command(c);

  struct command_info_t* elem = bsearch(&lookup_cmd,
					command_info,
					sizeof(command_info) / sizeof(struct command_info_t),
					sizeof(struct command_info_t),
					command_info_compare);
  if (NULL == elem)
    {
      return 0;
    }

  switch (elem->cmd_type)
    {
    case cmd_type_none:
    case cmd_type_nibble:
      command->data = NULL;
      command->size = 0;
      return offset + 1;
    case cmd_type_byte:
      command->data = vgm->buffer + offset + 1;
      command->size = 1;
      return offset + 2;
    case cmd_type_byte_byte:
    case cmd_type_short:
      command->data = vgm->buffer + offset + 1;
      command->size = 2;
      return offset + 3;
    case cmd_type_short_byte:
    case cmd_type_byte_byte_byte:
      command->data = vgm->buffer + offset + 1;
      command->size = 3;
      return offset + 4;
    case cmd_type_short_short:
    case cmd_type_int:
      command->data = vgm->buffer + offset + 1;
      command->size = 4;
      return offset + 5;
    case cmd_type_data_block:
      {
	command->data = vgm->buffer + offset + 2;
	uint32_t data_size = parse_uint (vgm->buffer, offset + 3, vgm->size);
	command->size = vgm->size - (offset + 2);
	return offset + 7 + data_size;
      }
    default:
      fprintf(stderr, "not found in lookup\n");
      return 0;
    };

  return 0;
}

int
vgm_process_command (FILE *fp, VgmCommand *command)
{
  uint8_t lookup_cmd = reduce_command(command->command);

  struct command_info_t* elem = bsearch(&lookup_cmd,
					command_info,
					sizeof(command_info) / sizeof(struct command_info_t),
					sizeof(struct command_info_t),
					command_info_compare);
  if (NULL == elem)
      return 0;

  char str[1024];
  switch (elem->cmd_type)
    {
    case cmd_type_none:
      snprintf(str, sizeof(str), "%s", elem->short_desc);
      break;
    case cmd_type_nibble:
      snprintf(str, sizeof(str), elem->short_desc,
	       (command->command & 0x0f));
      break;
    case cmd_type_byte:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_uchar(command->data, 0, command->size));
      break;
    case cmd_type_byte_byte:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_uchar(command->data, 0, command->size),
	       parse_uchar(command->data, 1, command->size));
      break;
    case cmd_type_short:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_ushort(command->data, 0, command->size));
      break;
    case cmd_type_short_byte:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_ushort(command->data, 0, command->size),
	       parse_uchar(command->data, 2, command->size));
      break;
    case cmd_type_byte_byte_byte:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_uchar(command->data, 0, command->size),
	       parse_uchar(command->data, 1, command->size),
	       parse_uchar(command->data, 2, command->size));
      break;
    case cmd_type_short_short:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_ushort(command->data, 0, command->size),
	       parse_ushort(command->data, 2, command->size));
      break;
    case cmd_type_int:
      snprintf(str, sizeof(str), elem->short_desc,
	       parse_uint(command->data, 0, command->size));
      break;
    case cmd_type_data_block:
      {
	uint8_t data_type = parse_uchar(command->data, 0, command->size);
	uint32_t data_size = parse_uint(command->data, 1, command->size);
	snprintf(str, sizeof(str), elem->short_desc, data_type, data_size);
	break;
      }
    default:
      fprintf(stderr, "not found in lookup\n");
      return -1;
    };

  fprintf (fp, "%s\n", str);
  return (elem->action_type == action_type_eos) ? 1 : 0;

/* // Saving for future implementation
  if (command->command == 0x54)
    {
      uint8_t data = command->data[1];
      uint8_t reg = command->data[0];
      fprintf (fp, "[YM2151] [%#04x] <- %#04x", reg, data);
      switch (reg)
        {
        case 0x01:
          fprintf (fp, ", (TEST & LFO RESET)");
          break;
        case 0x08:
          fprintf (fp, ", (KEY ON)");
          break;
        case 0x0f:
          fprintf (fp, ", (NOISE ENABLE, NOISE FREQUENCY)");
          break;
        case 0x11:
          fprintf (fp, ", (CLOCK A1)");
          break;
        case 0x12:
          fprintf (fp, ", (CLOCK A2)");
          break;
        case 0x13:
          fprintf (fp, ", (CLOCK B)");
          break;
        case 0x14:
          fprintf (fp, ", (CLOCK FUNCTIONS)");
          break;
        case 0x18:
          fprintf (fp, ", (LOW FREQUENCY)");
          break;
        case 0x19:
          fprintf (fp, ", (PHASE AND AMP MODULATION)");
          break;
        case 0x1b:
          fprintf (fp, ", (CONTROL OUTPUT & WAVE FORM SELECT)");
          break;
        case 0x20:
          fprintf (fp, ", (CHANNEL CONTROL)");
          break;
        };
      if (reg >= 0x28 && reg < 0x30)
        fprintf (fp, ", (KEY CODE)");
      if (reg >= 0x30 && reg < 0x38)
        fprintf (fp, ", (KEY FRACTION)");
      if (reg >= 0x38 && reg < 0x40)
        fprintf (fp, ", (PHASE & AMP MODULATION SENS)");
      if (reg >= 0x40 && reg < 0x60)
        fprintf (fp, ", (DETUNE & PHASE MULTIPLY)");
      if (reg >= 0x60 && reg < 0x80)
        fprintf (fp, ", (TOTAL LEVEL)");
      if (reg >= 0x80 && reg < 0xa0)
        fprintf (fp, ", (EG ATTACK)");
      if (reg >= 0xa0 && reg < 0xc0)
        fprintf (fp, ", (EG DELAY 1)");
      if (reg >= 0xc0 && reg < 0xe0)
        fprintf (fp, ", (EG DELAY 2)");
      if (reg >= 0xe0)
        fprintf (fp, ", (EG DECAY LEVEL, RELEASE RATE)");
      fprintf (fp, "\n");
      return 0;
    }
*/
}

