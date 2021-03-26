#ifndef DECODE_H
#define DECODE_H

#include <stdlib.h>


#define VGM_FT_UNKNOWN 0
#define VGM_FT_VGM 1
#define VGM_FT_VGZ 2

size_t load_file(const char *filename, char **buffer);

int file_type(const char *buffer, size_t size);
size_t decompress(char **output, const char *buffer, size_t size);


#endif
