#include <stdio.h>
#include <zlib.h>
#include <argp.h>

#include "vgm.h"
#include "args.h"

int main(int argc, char* argv[])
{
  struct arguments_t arguments;
  arguments.silent = 0;
  arguments.verbose = 0;

  parse_args(argc, argv, &arguments);
  printf("Hello world\n");
  return 0;
}
