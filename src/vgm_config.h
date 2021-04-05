#ifndef VGM_CONFIG_H
#define VGM_CONFIG_H

#include <stdlib.h>
#include <stdint.h>


enum cmd_type_t {
  cmd_type_none,
  cmd_type_nibble,
  cmd_type_nibble_inc,
  cmd_type_byte,
  cmd_type_byte_byte,
  cmd_type_short,
  cmd_type_short_byte,
  cmd_type_byte_byte_byte,
  cmd_type_short_short,
  cmd_type_int,
  cmd_type_data_block,
};

enum action_type_t {
  action_type_none,
  action_type_wait,
  action_type_game_gear_pcm,
  action_type_psg,
  action_type_ym2413,
  action_type_ym2612,
  action_type_ym2151,
  action_type_ym2203,
  action_type_ym2608,
  action_type_ym2610,
  action_type_ym3812,
  action_type_ym3526,
  action_type_y8950,
  action_type_ymz280b,
  action_type_ymf262,
  action_type_reserved,
  action_type_data_block,
  action_type_eos,
  action_type_sega_pcm,
  action_type_c352,
};

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

extern const struct command_info_t command_info[];
extern const size_t command_info_size;

extern const struct attr_name_t attribs[];
extern const size_t attribs_size;


#endif // VGM_CONFIG_H
