#include "vgm_helper.h"

#include <assert.h>
#include <string.h>

#include "vgm.h"
#include "vgm_config.h"

uint32_t parse_uint(const uint8_t *buffer, int offset, size_t size) {
  assert(buffer);
  assert(size >= 4);
  union {
    uint8_t c[4];
    uint32_t v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset + 1];
  im.c[2] = buffer[offset + 2];
  im.c[3] = buffer[offset + 3];
  return im.v;
}

uint32_t parse_ushort(const uint8_t *buffer, int offset, size_t size) {
  assert(buffer);
  assert(size >= 2);
  union {
    uint8_t c[2];
    uint16_t v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset + 1];
  return im.v;
}

uint32_t parse_uchar(const uint8_t *buffer, int offset, size_t size) {
  assert(buffer);
  assert(size >= 1);
  return (uint8_t)buffer[offset];
}

uint32_t parse_bcd(const uint8_t *buffer, int offset, size_t size) {
  assert(buffer);
  assert((size - offset) >= 4);
  uint32_t value = 0;
  for (int i = offset + 3; i >= offset; --i) {
    uint8_t c = buffer[i];
    value *= 10;
    value += c >> 4;
    value *= 10;
    value += c % 16;
  }
  return value;
}

int attr_info_compare(const void *key, const void *member) {
  int k = *((int *)key);
  int m = ((struct attr_name_t *)member)->id;
  return k - m;
}

int command_info_compare(const void *key, const void *member) {
  int16_t k = *((uint8_t *)key);
  int16_t m = ((struct command_info_t *)member)->cmd;
  return k - m;
}

uint8_t reduce_command(uint8_t cmd) {
  if ((0x30 <= cmd && 0x4f > cmd) || (0x70 <= cmd && 0x90 > cmd))
    return cmd & 0xf0;
  if (0xa1 <= cmd && 0xb0 > cmd) return 0xa1;
  if (0xc9 <= cmd && 0xd0 > cmd) return 0xc9;
  if (0xd7 <= cmd && 0xe0 > cmd) return 0xd7;
  if (0xe2 <= cmd) return 0xe2;
  return cmd;
}

char *get_attr_name(int attr) {
  struct attr_name_t *elem = bsearch(&attr, attribs, attribs_size,
                                     sizeof(attribs[0]), attr_info_compare);
  if (NULL == elem) return NULL;
  return elem->name;
}

size_t get_single_tag(char *dst, size_t n, const struct vgm_t *vgm, int attr,
                      size_t count) {
  uint32_t val;
  if ((val = vgm_get_attr(vgm, attr))) {
    if (count++) strncat(dst, ", ", n);
    const char *name = get_attr_name(attr);
    assert(name);
    char str[128];
    snprintf(str, sizeof(str), "%s(%d)", name, val);
    strncat(dst, str, n);
  }
  return count;
}
