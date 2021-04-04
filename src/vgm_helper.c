#include "vgm_helper.h"

#include <assert.h>

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
