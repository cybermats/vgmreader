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
  FILE *fp = fopen(arguments.input_file, "rb");
  if (NULL == fp)
    {
      perror ("Unable to open file\n");
      return -1;
    }
  size_t size = load_file (fp, &buffer);
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

  struct vgm_t *vgm = vgm_create (buffer, 0, size);
  if (!vgm)
    {
      fprintf (stderr, "Malformed VGM file.\n");
      return -1;
    }

  printf ("Version: %d, ", vgm_get_attr(vgm, VGM_VERSION));

  char tags[1024];
  tags[0] = 0;
  vgm_get_tags (tags, sizeof(tags), vgm);
  printf ("Tags: [%s], ", tags);

  uint32_t total_num_samples = vgm_get_attr(vgm, VGM_TOTAL_NUM_SAMPLES);
  uint32_t loop_offset = vgm_get_attr(vgm, VGM_LOOP_OFFSET);
  uint32_t loop_num_samples = vgm_get_attr(vgm, VGM_LOOP_NUM_SAMPLES);
  printf("Samples: %d", total_num_samples);
  if (loop_offset) {
    printf(", Loop Samples: %d", loop_num_samples);
  }
  printf("\n");

  size_t offset = vgm_get_attr(vgm, VGM_DATA_OFFSET) + 0x34;
  while (offset)
    {
      struct vgm_command_t cmd;
      offset = vgm_next_command(&cmd, vgm, offset);
      vgm_process_command(stdout, &cmd);      
    }

  printf ("\n");

  return 0;
}
