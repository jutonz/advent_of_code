#ifndef DAY3_2
#define DAY3_2

struct LineList {
  char **lines;
  int length;
};

void run3_2(char*);
struct LineList _drop_lines_with_ch_at_pos(char **lines, int num_lines, int, char char_to_drop);
int _calculate_oxygen_generator_rating(char **lines, int num_lines);
int _calculate_co2_scrubber_rating(char **lines, int num_lines);

#endif
