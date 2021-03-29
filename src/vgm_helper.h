#ifndef VGM_HELPER_H
#define VGM_HELPER_H

#include <stdlib.h>

unsigned int
parse_uint (const unsigned char *buffer, int offset, size_t size);
unsigned int
parse_ushort (const unsigned char *buffer, int offset, size_t size);
unsigned int
parse_uchar (const unsigned char *buffer, int offset, size_t size);
unsigned int
parse_bcd (const unsigned char *buffer, int offset, size_t size);



#endif
