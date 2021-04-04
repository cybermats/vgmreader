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

typedef struct {
  const uint8_t *buffer;
  size_t size;
} Vgm;

typedef struct {
  uint8_t command;
  const uint8_t *data;
  size_t size;
} VgmCommand;

typedef enum {
  unknown = 0,
  none,
  game_gear,
  psg,
  ym2413,

} VgmCpu;

Vgm *vgm_create(const unsigned char *buffer, size_t start_offset, size_t buffer_size);
void vgm_free(Vgm *vgm);
size_t vgm_get_tags(char *dst, size_t n, const Vgm *vgm);

uint32_t vgm_get_attr(const Vgm *vgm, int attribute);

size_t vgm_next_command(VgmCommand *cmd, const Vgm *vgm, size_t offset);

VgmCpu vgm_get_command_cpu(const VgmCommand *command);

int vgm_process_command(FILE *fp, VgmCommand *command);

int vgm_validate_buffer(const uint8_t *buffer, size_t size);

#endif
