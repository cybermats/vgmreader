#include "decode.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <zlib.h>

static char vgz[] = {0x1f, 0x8b};
static char vgm[] = "Vgm ";

#define CHUNK 16384

int file_type(const uint8_t *buffer, size_t size) {
  if (!buffer || !size) return VGM_FT_UNKNOWN;

  if (size < 2) return VGM_FT_UNKNOWN;

  if (memcmp(buffer, vgz, 2) == 0) return VGM_FT_VGZ;

  if (size < 4) return VGM_FT_UNKNOWN;

  if (memcmp(buffer, vgm, 4) == 0) return VGM_FT_VGM;

  return VGM_FT_UNKNOWN;
}

size_t decompress(uint8_t **output, const uint8_t *buffer, size_t size) {
  if (!size) return 0;

  int ret;
  unsigned have;
  z_stream strm;
  size_t offset = 0;
  unsigned char out[CHUNK];
  *output = (uint8_t *)malloc(CHUNK);
  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit2(&strm, (15 + 32));
  if (ret != Z_OK) {
    free(*output);
    return 0;
  }

  /* decompress until deflate stream ends or end of buffer */
  do {
    strm.avail_in = size;
    strm.next_in = (uint8_t *)buffer;
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
        case Z_MEM_ERROR:
          (void)inflateEnd(&strm);
          free(*output);
          return 0;
      }
      have = CHUNK - strm.avail_out;
      memcpy(*output + offset, out, have);
      offset += have;
      uint8_t *b = realloc(*output, offset + CHUNK);
      if (!b) {
        (void)inflateEnd(&strm);
        free(*output);
        return 0;
      }
      *output = b;
    } while (strm.avail_out == 0);
    /* done when inflate says it's done */
  } while (ret != Z_STREAM_END);
  /* clean up and return */
  (void)inflateEnd(&strm);

  return offset;
}

int read_file(FILE *fp, uint8_t **buffer, size_t *size) {
  if (fseek(fp, 0, SEEK_END)) return -1;
  long s = ftell(fp);
  if (s < 0) return -1;
  if (fseek(fp, 0, SEEK_SET)) return -1;
  uint8_t *b = malloc(s);
  size_t ret = fread((void *)(b), 1, s, fp);
  if (ferror(fp) != 0) {
    free(b);
    return -1;
  }
  *buffer = b;
  *size = ret;
  return 0;
}

int resolve_buffer(uint8_t **buffer, size_t *size) {
  int ft = file_type(*buffer, *size);
  if (ft == VGM_FT_UNKNOWN) return -1;
  if (ft == VGM_FT_VGM) return 0;

  // We have a compressed file.
  uint8_t *uncompressed;
  size_t un_size = decompress(&uncompressed, *buffer, *size);
  if (un_size == 0) return -2;

  // Replace the existing buffer;
  free(*buffer);
  *buffer = uncompressed;
  *size = un_size;
  return 0;
}

size_t load_file(FILE *fp, uint8_t **buffer) {
  assert(fp);
  assert(buffer);
  size_t size;
  int res = read_file(fp, buffer, &size);
  if (res != 0) {
    perror("Unable to read file\n");
    return 0;
  }

  res = resolve_buffer(buffer, &size);
  if (res == -1) {
    fprintf(stderr, "Unknown file type.\n");
    free(*buffer);
    *buffer = NULL;
    return 0;
  }
  if (res == -2) {
    fprintf(stderr, "Unable to decompress file.\n");
    free(*buffer);
    *buffer = NULL;
    return 0;
  }

  return size;
}
