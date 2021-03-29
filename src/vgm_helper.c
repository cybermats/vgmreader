#include "vgm_helper.h"
#include <assert.h>


unsigned int
parse_uint (const unsigned char *buffer, int offset, size_t size)
{
  assert (buffer);
  assert (size >= 4);
  union
  {
    char c[4];
    unsigned int v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset + 1];
  im.c[2] = buffer[offset + 2];
  im.c[3] = buffer[offset + 3];
  return im.v;
}

unsigned int
parse_ushort (const unsigned char *buffer, int offset, size_t size)
{
  assert (buffer);
  assert (size >= 2);
  union
  {
    char c[2];
    unsigned short v;
  } im;
  im.c[0] = buffer[offset];
  im.c[1] = buffer[offset + 1];
  return im.v;
}

unsigned int
parse_uchar (const unsigned char *buffer, int offset, size_t size)
{
  assert (buffer);
  assert (size >= 1);
  return (unsigned char)buffer[offset];
}

unsigned int
parse_bcd (const unsigned char *buffer, int offset, size_t size)
{
  assert (buffer);
  assert ((size - offset) >= 4);
  unsigned int value = 0;
  for (int i = offset + 3; i >= offset; --i)
    {
      unsigned char c = buffer[i];
      value *= 10;
      value += c >> 4;
      value *= 10;
      value += c % 16;
    }
  return value;
}
