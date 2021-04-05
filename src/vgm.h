#ifndef VGM_H
#define VGM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Version 1.00
#define VGM_EOF 0x04
#define VGM_VERSION 0x08
#define VGM_SN76489 0x0c
#define VGM_YM2413 0x10
#define VGM_GD3_OFFSET 0x14
#define VGM_TOTAL_NUM_SAMPLES 0x18
#define VGM_LOOP_OFFSET 0x1c
#define VGM_LOOP_NUM_SAMPLES 0x20

// Version 1.01
#define VGM_RATE 0x24

// Version 1.10
#define VGM_SN76489_FEEDBACK 0x28         // 16 bits
#define VGM_SN76489_SHIFT_REG_WIDTH 0x2a  // 8 bits

// Version 1.51
#define VGM_SN76489_FLAGS 0x2b  // 8 bits

// Version 1.10
#define VGM_YM2612 0x2c
#define VGM_YM2151 0x30

// Version 1.50
#define VGM_DATA_OFFSET 0x34

// Version 1.51
#define VGM_SEGA_PCM 0x38
#define VGM_SEGA_PCM_INTERFACE_REG 0x3c
#define VGM_RF5C68 0x40
#define VGM_YM2203 0x44
#define VGM_YM2608 0x48
#define VGM_YM2610 0x4c
#define VGM_YM3812 0x50
#define VGM_YM3526 0x54
#define VGM_Y8950 0x58
#define VGM_YMF262 0x5c
#define VGM_YMF278B 0x60
#define VGM_YMF271 0x64
#define VGM_YMZ280B 0x68
#define VGM_RF5C164 0x6c
#define VGM_PWM 0x70
#define VGM_AY8910 0x74
#define VGM_AY8910_CHIP_TYPE 0x78  // 8 bits
#define VGM_AY8910_FLAGS 0x79      // 8 bits
#define VGM_YM2203_FLAGS 0x7a      // 8 bits
#define VGM_YM2608_FLAGS 0x7b      // 8 bits

// Version 1.60

// Version 1.51
#define VGM_LOOP_MODIFIER 0x7f  // 8 bits

enum cmd_type_t {
  cmd_type_none = 0,
  cmd_type_nibble,
  cmd_type_nibble_inc,
  cmd_type_byte,
  cmd_type_byte_byte,
  cmd_type_short,
  cmd_type_short_byte,
  cmd_type_byte_byte_byte,
  cmd_type_short_short,
  cmd_type_int,
  cmd_type_data_block,
};

enum action_type_t {
  action_type_none = 0,
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

struct vgm_t {
  const uint8_t *buffer;
  size_t size;
};

struct vgm_command_t {
  uint8_t command;
  enum cmd_type_t cmd_type;
  enum action_type_t action;
  const uint8_t *data;
  size_t size;
};

struct vgm_t *vgm_create(const unsigned char *buffer,
			 size_t start_offset,
                         size_t buffer_size);
void vgm_free(struct vgm_t *vgm);
size_t vgm_get_tags(char *dst, size_t n, const struct vgm_t *vgm);

uint32_t vgm_get_attr(const struct vgm_t *vgm, int attribute);

size_t vgm_next_command(struct vgm_command_t *cmd,
			const struct vgm_t *vgm,
			size_t offset);

int vgm_process_command(FILE *fp,
			const struct vgm_command_t *cmd);
int vgm_cmd_to_string(char *str, size_t size,
		      const struct vgm_command_t *cmd);
int vgm_validate_buffer(const uint8_t *buffer, size_t size);

#endif
