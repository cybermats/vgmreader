#include <string.h>
#include <assert.h>
#include <zlib.h>
#include <stdio.h>
#include "decode.h"

static char vgz[] = { 0x1f, 0x8b };
static char vgm[] = "Vgm ";

#define CHUNK 16384

int file_type(const unsigned char *buffer, size_t size)
{
  if (!buffer || !size)
    return VGM_FT_UNKNOWN;

  if (size < 2)
    return VGM_FT_UNKNOWN;
  
  if (memcmp(buffer, vgz, 2) == 0)
    return VGM_FT_VGZ;

  if (size < 4)
    return VGM_FT_UNKNOWN;
  
  if (memcmp(buffer, vgm, 4) == 0)
    return VGM_FT_VGM;

  
  return VGM_FT_UNKNOWN;
}

size_t decompress(unsigned char **output, const
		  unsigned char *buffer, size_t size)
{
  printf("decompress 1\n");
  if (!size)
    return 0;
  
  printf("decompress 2\n");
  int ret;
  unsigned have;
  z_stream strm;
  size_t offset = 0;
  unsigned char out[CHUNK];
  *output = malloc(CHUNK);
  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit2(&strm, (15 + 32));
  if (ret != Z_OK) {
    printf("decompress fail 1\n");
    free(*output);
    return 0;
  }

  printf("decompress 3\n");
  /* decompress until deflate stream ends or end of buffer */
  do {
    strm.avail_in = size;
    strm.next_in = (unsigned char*)buffer;
    /* run inflate() on input until output buffer not full */
    do {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      ret = inflate(&strm, Z_NO_FLUSH);
      assert(ret != Z_STREAM_ERROR); /* state not clobbered */
      switch (ret) {
      case Z_NEED_DICT:
	//	ret = Z_DATA_ERROR; /* and fall through */
      case Z_DATA_ERROR:
	printf("Msg: %s\n", strm.msg);
      case Z_MEM_ERROR:
	(void)inflateEnd(&strm);
	free(*output);
	printf("decompress fail 2 - %d\n", ret);
	return 0;
      }
      have = CHUNK - strm.avail_out;
      memcpy(&(*output[offset]), out, have);
      offset += have;
      char *b = realloc(*output, offset + CHUNK);
      if (!*b) {
	(void)inflateEnd(&strm);
	free(*output);
	printf("decompress fail 3\n");
	return 0;
      }
      *output = b;
    } while (strm.avail_out == 0);
    /* done when inflate says it's done */
  } while (ret != Z_STREAM_END);
  /* clean up and return */
  (void)inflateEnd(&strm);
  
  printf("decompress return\n");
  return offset;    
}
