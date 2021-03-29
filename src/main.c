#include <argp.h>
#include <stdio.h>

#include "args.h"
#include "decode.h"
#include "vgm.h"

int
main (int argc, char *argv[])
{
  struct arguments_t arguments;
  arguments.silent = 0;
  arguments.verbose = 0;

  parse_args (argc, argv, &arguments);

  unsigned char *buffer;
  size_t size = load_file (arguments.input_file, &buffer);
  if (size == 0)
    {
      fprintf (stderr, "Unable to parse file.\n");
      return -1;
    }

  if (!vgm_validate_buffer (buffer, size))
    {
      fprintf (stderr, "Not a VGM file.\n");
      return -1;
    }

  Vgm *vgm = vgm_create (buffer, 0, size);
  if (!vgm)
    {
      fprintf (stderr, "Malformed VGM file.\n");
      return -1;
    }

  printf ("Version: %d, ", vgm->version);

  char tags[1024];
  tags[0] = 0;
  vgm_get_tags (vgm, tags, 1024);
  printf ("Tags: (%s), ", tags);

  printf ("\n");

  return 0;
}
