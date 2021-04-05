#include "vgm_config.h"
#include "vgm.h"

const struct command_info_t command_info[] = {
    {0x30, cmd_type_byte, action_type_reserved, "[reserved]"},
    {0x40, cmd_type_byte_byte, action_type_reserved, "[reserved]"},

    {0x4f, cmd_type_byte, action_type_game_gear_pcm,
     "[Game Gear PCM] :6 <- %#04x"},
    {0x50, cmd_type_byte, action_type_psg, "[PSG] <- %#04x"},

    {0x51, cmd_type_byte_byte, action_type_ym2413, "[%#04x] <- %#04x"},
    {0x52, cmd_type_byte_byte, action_type_ym2612, "[%#04x]:0 <- %#04x"},
    {0x53, cmd_type_byte_byte, action_type_ym2612, "[%#04x]:1 <- %#04x"},
    {0x54, cmd_type_byte_byte, action_type_ym2151, "[YM2151] [%#04x] <- %#04x"},
    {0x55, cmd_type_byte_byte, action_type_ym2203, "[%#04x] <- %#04x"},
    {0x56, cmd_type_byte_byte, action_type_ym2608, "[%#04x]:0 <- %#04x"},
    {0x57, cmd_type_byte_byte, action_type_ym2608, "[%#04x]:1 <- %#04x"},
    {0x58, cmd_type_byte_byte, action_type_ym2610, "[%#04x]:0 <- %#04x"},
    {0x59, cmd_type_byte_byte, action_type_ym2610, "[%#04x]:1 <- %#04x"},
    {0x5a, cmd_type_byte_byte, action_type_ym3812, "[%#04x] <- %#04x"},
    {0x5b, cmd_type_byte_byte, action_type_ym3526, "[%#04x] <- %#04x"},
    {0x5c, cmd_type_byte_byte, action_type_y8950, "[%#04x] <- %#04x"},
    {0x5d, cmd_type_byte_byte, action_type_ymz280b, "[%#04x] <- %#04x"},
    {0x5e, cmd_type_byte_byte, action_type_ymf262, "[%#04x]:0 <- %#04x"},
    {0x5f, cmd_type_byte_byte, action_type_ymf262, "[%#04x]:1 <- %#04x"},

    {0x61, cmd_type_short, action_type_wait, "[Wait] Samples: %d"},
    {0x62, cmd_type_none, action_type_wait, "[Wait] One frame (60Hz)"},
    {0x63, cmd_type_none, action_type_wait, "[Wait] One frame (50Hz)"},

    {0x66, cmd_type_none, action_type_eos, "[EOS] End of sound data"},

    {0x67, cmd_type_data_block, action_type_data_block,
     "[Data Block] Data Type %#04x, Size %#04x"},

    // TODO: Fix nibble+1 for Wait
    {0x70, cmd_type_nibble_inc, action_type_wait, "[Wait] Samples: %d"},

    {0x80, cmd_type_nibble, action_type_ym2612,
     "[YM2612] [0x2a]:0 <- data bank, then wait %d samples"},

    {0xa1, cmd_type_byte_byte, action_type_reserved, "[reserved]"},

    {0xc0, cmd_type_short_byte, action_type_sega_pcm, "[%#06x] <- %#04x"},

    {0xc9, cmd_type_byte_byte_byte, action_type_reserved, "[reserved]"},
    {0xd7, cmd_type_byte_byte_byte, action_type_reserved, "[reserved]"},

    {0xe0, cmd_type_int, action_type_ym2612,
     "Seek to offset [%#010x] in PCM Data bank"},
    {0xe1, cmd_type_short_short, action_type_c352, "[%#06x] <- %#06x"},

    {0xe2, cmd_type_int, action_type_reserved, "reserved"},

};

const size_t command_info_size = sizeof command_info / sizeof *command_info;

const struct attr_name_t attribs[] = {
    { VGM_SN76489, "sn76489" },
    { VGM_EOF, "eof" },
    { VGM_VERSION, "version" },
    { VGM_SN76489, "sn76489" },
    { VGM_YM2413, "ym2413" },
    { VGM_GD3_OFFSET, "GD3 offset" },
    { VGM_TOTAL_NUM_SAMPLES, "total num samples" },
    { VGM_LOOP_OFFSET, "loop offset" },
    { VGM_LOOP_NUM_SAMPLES, "loop num samples" },
    { VGM_RATE, "rate" },
    { VGM_SN76489_FEEDBACK, "sn76489 feedback" },
    { VGM_SN76489_SHIFT_REG_WIDTH, "sn76489 shift register width" },
    { VGM_SN76489_FLAGS, "sn76489 flags" },
    { VGM_YM2612, "ym2612" },
    { VGM_YM2151, "ym2151" },
    { VGM_DATA_OFFSET, "data offset" },
    { VGM_SEGA_PCM, "SEGA PCM" },
    { VGM_SEGA_PCM_INTERFACE_REG, "SEGA PCM interface reg" },
    { VGM_RF5C68, "rf5c68" },
    { VGM_YM2203, "ym2203" },
    { VGM_YM2608, "ym2608" },
    { VGM_YM2610, "ym2610" },
    { VGM_YM3812, "ym3812" },
    { VGM_YM3526, "ym3526" },
    { VGM_Y8950, "y8950" },
    { VGM_YMF262, "ymf262" },
    { VGM_YMF278B, "ymf278b" },
    { VGM_YMF271, "ymf271" },
    { VGM_YMZ280B, "ymz280b" },
    { VGM_RF5C164, "rf5c164" },
    { VGM_PWM, "PWM" },
    { VGM_AY8910, "ay8910" },
    { VGM_AY8910_CHIP_TYPE, "ay8910 chip type" },
    { VGM_AY8910_FLAGS, "ay8910 flags" },
    { VGM_YM2203_FLAGS, "ym2203 flags" },
    { VGM_YM2608_FLAGS, "ym2608 flags" },
    { VGM_LOOP_MODIFIER, "loop modifier" },
  };

const size_t attribs_size = sizeof attribs / sizeof *attribs;
