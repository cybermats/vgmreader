#ifndef DECODE_H
#define DECODE_H

#include <stdlib.h>
#include <stdio.h>

#define VGM_FT_UNKNOWN 0
#define VGM_FT_VGM 1
#define VGM_FT_VGZ 2

size_t load_file (FILE *fp, uint8_t **buffer);

#endif
