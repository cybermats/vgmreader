#ifndef VGM_H
#define VGM_H

typedef struct
{
  unsigned int eof_offset;
  unsigned int version;
  unsigned int sn76489_clock;
  unsigned int ym2413_clock;
  unsigned int gd3_offset;
  unsigned int total_num_samples;
  unsigned int loop_offset;
  unsigned int loop_num_samples;
  unsigned int rate;
  unsigned int sn76489_feedback;
  unsigned int sn76489_shift_reg_width;
  unsigned int ym2612_clock;
  unsigned int ym2151_clock;
  unsigned int sn76489_flags;
  unsigned int sega_pcm_clock;
  unsigned int sega_pcm_int_reg;
  unsigned int rf5c68_clock;
  unsigned int ym2203_clock;
  unsigned int ym2608_clock;
  unsigned int ym2610_clock;
  unsigned int ym3812_clock;
  unsigned int ym3526_clock;
  unsigned int y8950_clock;
  unsigned int ymf262_clock;
  unsigned int ymf278b_clock;
  unsigned int ymf271_clock;
  unsigned int ymz280b_clock;
  unsigned int rf5c164_clock;
  unsigned int pwm_clock;
  unsigned int ay8910_clock;
  unsigned int ay8910_chip_type;
  unsigned int ay8910_flags;
  unsigned int ym2203_flags;
  unsigned int ym2608_flags;
  unsigned int loop_modifier;
  

  unsigned int data_offset;
} Vgm;

Vgm *vgm_create(const unsigned char *buffer, int offset, size_t size);
void vgm_free(Vgm *vgm);
size_t vgm_get_tags(const Vgm *vgm, char *dst, size_t size);

int vgm_validate_buffer(const unsigned char *buffer, size_t size);

unsigned int parse_uint(const unsigned char *buffer,
			int offset, size_t size);
unsigned int parse_ushort(const unsigned char *buffer,
			int offset, size_t size);
unsigned int parse_uchar(const unsigned char *buffer,
			int offset, size_t size);
unsigned int parse_bcd(const unsigned char *buffer,
		       int offset, size_t size);

#endif
