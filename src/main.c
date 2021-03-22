#include <stdio.h>
#include <zlib.h>
#include "vgm.h"

int main(int argc, char* argv[])
{
  Vgm *vgm;
  z_stream strm;
  inflateInit(&strm);
  
  printf("Hello world\n");
  return 0;
}
