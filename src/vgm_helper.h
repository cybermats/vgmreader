#ifndef VGM_HELPER_H
#define VGM_HELPER_H

#include <stdint.h>
#include <stdlib.h>

#include "vgm_config.h"

struct vgm_t;

uint32_t parse_uint(const uint8_t *buffer, int offset, size_t size);
uint32_t parse_ushort(const uint8_t *buffer, int offset, size_t size);
uint32_t parse_uchar(const uint8_t *buffer, int offset, size_t size);
uint32_t parse_bcd(const uint8_t *buffer, int offset, size_t size);

int attr_info_compare(const void *key, const void *member);
char *get_attr_name(int attr);
size_t get_single_tag(char *dst, size_t n, const struct vgm_t *vgm, int attr,
                      size_t count);
int command_info_compare(const void *key, const void *member);
uint8_t reduce_command(uint8_t cmd);

#endif
