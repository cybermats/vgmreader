#ifndef VGM_HELPER_H
#define VGM_HELPER_H

#include <stdlib.h>
#include <stdint.h>

uint32_t
parse_uint (const uint8_t *buffer, int offset, size_t size);
uint32_t
parse_ushort (const uint8_t *buffer, int offset, size_t size);
uint32_t
parse_uchar (const uint8_t *buffer, int offset, size_t size);
uint32_t
parse_bcd (const uint8_t *buffer, int offset, size_t size);



#endif
