#include "args.h"

#include <argp.h>

const char *argp_program_version = "vgmreader 0.1";
const char *argp_program_bug_address = "Mats Fredriksson <cybermats@gmail.com>";

static char doc[] = "VGM file reader";

static char args_doc[] = "file";

static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {"quiet", 'q', 0, 0, "Don't produce any output", 0},
    {"silent", 's', 0, OPTION_ALIAS, 0, 0},
    {"header", 'h', 0, 0, "Print headers", 0},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments_t *arguments = state->input;

  switch (key) {
    case 'q':
    case 's':
      arguments->silent = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'h':
      arguments->header = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1) /* Too many arguments */
        argp_usage(state);
      arguments->input_file = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1) /* Not enough arguments. */
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

int parse_args(int argc, char *argv[], struct arguments_t *arguments) {
  return argp_parse(&argp, argc, argv, 0, 0, arguments);
}
