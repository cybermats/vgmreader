#include <stdio.h>
#include <zlib.h>
#include <argp.h>

#include "vgm.h"
#include "args.h"
#include "decode.h"

void print_buffer(const unsigned char *buffer, size_t size)
{
  for (size_t i = 0; i < 16; ++i) {
    printf("%02x ", buffer[i]);
    if (i % 8 == 7) printf(" ");
    if (i % 16 == 15) printf("\n");
  }
}


int read_file(const char *filename, unsigned char **buffer, size_t *size)
{
  FILE *f = fopen(filename, "r");
  if (!f)
    return -1;
  if (fseek(f, 0, SEEK_END))
    return -2;
  long s = ftell(f);
  if (s < 0)
    return -3;
  if (fseek(f, 0, SEEK_SET))
    return -4;
  *buffer = malloc(s);
  size_t ret = fread((void*)(*buffer), 1, s, f);
  printf("fread: %d\n", ret);
  print_buffer(*buffer, s);
  if (ferror(f) != 0) {
    free(*buffer);
    return -4;
  }
  return 0;
}

int resolve_buffer(unsigned char **buffer, size_t *size)
{
  int ft = file_type(*buffer, *size);
  printf("File Type: %x\n", ft);
  if (ft == VGM_FT_UNKNOWN)
    return -1;
  if (ft == VGM_FT_VGM)
    return 0;

  // We have a compressed file.
  unsigned char *uncompressed;
  size_t un_size = decompress(&uncompressed, *buffer, *size);
  if (un_size == 0)
    return -2;

  // Replace the existing buffer;
  free(*buffer);
  *buffer = uncompressed;
  *size = un_size;
  return 0;
}


int main(int argc, char* argv[])
{
  struct arguments_t arguments;
  arguments.silent = 0;
  arguments.verbose = 0;

  parse_args(argc, argv, &arguments);

  unsigned char *buffer;
  size_t size;

  char msg[256];
  int res = read_file(arguments.input_file, &buffer, &size);
  printf("File size: %d\n", size);
  if (res == -5) {
    fprintf(stderr, "Unable to open file [%s]\n", arguments.input_file);
    return -1;
  }
  if (res != 0) {
    snprintf(msg, sizeof(msg),
	     "Unable to read file [%s]\n", arguments.input_file);
    perror(msg);
    return -1;
  }
  
  res = resolve_buffer( &buffer, &size);
  if (res == -1) {
    fprintf(stderr, "Unknown file type.\n");
    return -1;
  }
  if (res == -2) {
    fprintf(stderr, "Unable to decompress file.\n");
    return -1;
  }
  
  
  return 0;
}
