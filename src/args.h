#ifndef ARGS_H
#define ARGS_H

struct arguments_t
{
  char *input_file;
  int header;
  int silent, verbose;
};

int parse_args (int argc, char *argv[], struct arguments_t *arguments);

#endif
