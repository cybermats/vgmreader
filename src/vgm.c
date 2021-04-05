#include "vgm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "vgm_config.h"
#include "vgm_helper.h"

struct vgm_t *vgm_create(const unsigned char *buffer, size_t start_offset,
                         size_t buffer_size) {
  const size_t header_size = buffer_size - start_offset;
  if (header_size < 256) return NULL;
  struct vgm_t *vgm;
  vgm = malloc(sizeof(struct vgm_t));
  vgm->buffer = buffer;
  vgm->size = buffer_size;
  return vgm;
}

void vgm_free(struct vgm_t *vgm) {
  free(vgm);
  return;
}

size_t vgm_get_tags(char *dst, size_t n, const struct vgm_t *vgm) {
  int count = 0;
  static int tag_attrs[] = {
      VGM_SN76489, VGM_YM2413,  VGM_YM2612, VGM_YM2151,  VGM_SEGA_PCM,
      VGM_RF5C68,  VGM_YM2203,  VGM_YM2608, VGM_YM2610,  VGM_YM3812,
      VGM_YM3526,  VGM_Y8950,   VGM_YMF262, VGM_YMF278B, VGM_YMF271,
      VGM_YMZ280B, VGM_RF5C164, VGM_PWM,    VGM_AY8910,  VGM_YM2203,
      VGM_YM2608,
  };

  for (size_t i = 0; i < (sizeof(tag_attrs) / sizeof(tag_attrs[0])); ++i) {
    count = get_single_tag(dst, n, vgm, tag_attrs[i], count);
  }

  return 0;
}

unsigned int vgm_get_attr(const struct vgm_t *vgm, int attribute) {
  unsigned int version = parse_bcd(vgm->buffer, VGM_VERSION, vgm->size);
  if (attribute == VGM_VERSION) {
    return version;
  }

  // Handle default values of attributes

  if (version < 101) {
    if (attribute == VGM_RATE) return 0;
  }
  if (version < 110) {
    if (attribute == VGM_SN76489_FEEDBACK) return 0x09;
    if (attribute == VGM_SN76489_SHIFT_REG_WIDTH) return 0x10;
    if (attribute == VGM_YM2612 || attribute == VGM_YM2151)
      attribute = VGM_YM2413;
  }
  if (version < 150) {
    if (attribute == VGM_DATA_OFFSET) return 0x40;
  }
  if (version < 151) {
    if (attribute == VGM_SN76489_FLAGS || attribute == VGM_SEGA_PCM ||
        attribute == VGM_SEGA_PCM_INTERFACE_REG || attribute == VGM_RF5C68 ||
        attribute == VGM_YM2203 || attribute == VGM_YM2608 ||
        attribute == VGM_YM2610 || attribute == VGM_YM3812 ||
        attribute == VGM_YM3526 || attribute == VGM_Y8950 ||
        attribute == VGM_YMF262 || attribute == VGM_YMF278B ||
        attribute == VGM_YMF271 || attribute == VGM_YMZ280B ||
        attribute == VGM_RF5C164 || attribute == VGM_PWM ||
        attribute == VGM_AY8910 || attribute == VGM_AY8910_CHIP_TYPE ||
        attribute == VGM_AY8910_FLAGS || attribute == VGM_YM2203_FLAGS ||
        attribute == VGM_YM2608_FLAGS || attribute == VGM_LOOP_MODIFIER)
      return 0x0;
  }

  // Handle special cases for attributes (i.e. shorts, chars and bcd)

  switch (attribute) {
    case VGM_SN76489_FEEDBACK:
      return parse_ushort(vgm->buffer, attribute, vgm->size);
    case VGM_SN76489_SHIFT_REG_WIDTH:
    case VGM_AY8910_CHIP_TYPE:
    case VGM_AY8910_FLAGS:
    case VGM_YM2203_FLAGS:
    case VGM_YM2608_FLAGS:
    case VGM_SN76489_FLAGS:
    case VGM_LOOP_MODIFIER:
      return parse_uchar(vgm->buffer, attribute, vgm->size);
    case VGM_VERSION:
      return parse_bcd(vgm->buffer, attribute, vgm->size);
    default:  // Handle default case which is int.
      return parse_uint(vgm->buffer, attribute, vgm->size);
  }
}

int vgm_validate_buffer(const unsigned char *buffer, size_t size) {
  if (size < 4) return 0;
  if (strncmp((const char *)buffer, "Vgm ", 4) == 0) return 1;
  return 0;
}

size_t vgm_next_command(struct vgm_command_t *cmd, const struct vgm_t *vgm,
                        size_t offset) {
  assert(vgm);
  assert(vgm->buffer);
  assert(cmd);
  uint8_t c = vgm->buffer[offset];
  uint8_t lookup_cmd = reduce_command(c);

  struct command_info_t *elem =
      bsearch(&lookup_cmd, command_info, command_info_size,
              sizeof(struct command_info_t), command_info_compare);

  if (!elem) return 0;

  cmd->command = c;
  cmd->cmd_type = elem->cmd_type;
  cmd->action = elem->action_type;

  switch (elem->cmd_type) {
    case cmd_type_none:
    case cmd_type_nibble:
    case cmd_type_nibble_inc:
      cmd->data = NULL;
      cmd->size = 0;
      return offset + 1;
    case cmd_type_byte:
      cmd->data = vgm->buffer + offset + 1;
      cmd->size = 1;
      return offset + 2;
    case cmd_type_byte_byte:
    case cmd_type_short:
      cmd->data = vgm->buffer + offset + 1;
      cmd->size = 2;
      return offset + 3;
    case cmd_type_short_byte:
    case cmd_type_byte_byte_byte:
      cmd->data = vgm->buffer + offset + 1;
      cmd->size = 3;
      return offset + 4;
    case cmd_type_short_short:
    case cmd_type_int:
      cmd->data = vgm->buffer + offset + 1;
      cmd->size = 4;
      return offset + 5;
    case cmd_type_data_block: {
      cmd->data = vgm->buffer + offset + 2;
      uint32_t data_size = parse_uint(vgm->buffer, offset + 3, vgm->size);
      cmd->size = vgm->size - (offset + 2);
      return offset + 7 + data_size;
    }
  };

  fprintf(stderr, "not found in lookup\n");
  return 0;
}

int vgm_process_command(FILE *fp, const struct vgm_command_t *cmd) {
  char str[1024];
  int res = vgm_cmd_to_string(str, sizeof str, cmd);
  fprintf(fp, "%s\n", str);
  return res;
}

int vgm_cmd_to_string(char *str, size_t size, const struct vgm_command_t *cmd) {
  const char *action = get_action_name(cmd->action);
  char short_desc[1024];
  get_cmd_desc(short_desc, sizeof short_desc, cmd);

  int action_len = snprintf(str, size, "[%s]", action);
  if (action_len > (int)size) {
    return -1;
  }
  if (action_len < 0) {
    return -2;
  }

  size_t desc_len = strnlen(short_desc, sizeof short_desc);
  if (desc_len == 0) return 0;

  if (action_len + desc_len + /* space */ 1 + /* null-term */ 1 > size) {
    return -1;
  }

  strncat(str, " ", size);
  strncat(str, short_desc, size);

  return 0;

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
