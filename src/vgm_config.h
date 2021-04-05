#ifndef VGM_CONFIG_H
#define VGM_CONFIG_H

#include <stdint.h>
#include <stdlib.h>
#include "vgm.h"
struct attr_name_t {
  int id;
  char name[32];
};

struct command_info_t {
  uint8_t cmd;
  enum cmd_type_t cmd_type;
  enum action_type_t action_type;
  char short_desc[128];
};

struct action_info_t {
  enum action_type_t id;
  char desc[128];
};

extern const struct command_info_t command_info[];
extern const size_t command_info_size;

extern const struct attr_name_t attribs[];
extern const size_t attribs_size;

extern const struct action_info_t action_info[];
extern const size_t action_info_size;

#endif  // VGM_CONFIG_H
