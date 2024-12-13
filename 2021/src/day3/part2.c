#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file.h"
#include "./part2.h"

char* _load_file(char *file) {
  FILE *fp = fopen(file, "rb");
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, fsize, 1, fp);
  fclose(fp);

  buffer[fsize] = '\0';

  return buffer;
}

int _num_lines(char *string) {
  int lines = 0;

  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == '\n')
      lines++;
  }

  return lines;
}

char** _split_lines(char *string, int num_lines) {
  char *context = NULL;
  char *line = strtok_r(string, "\n", &context);
  int line_length = strlen(line);
  char **lines = (char**)malloc(sizeof(char) * line_length * num_lines);
  lines[0] = line;

  int index = 1;
  while(line != NULL) {
    line = strtok_r(NULL, "\n", &context);

    if (line)
      lines[index++] = line;
  }

  return lines;
}

struct LineList _drop_lines_with_ch_at_pos(char **lines, int num_lines, int position, char char_to_drop) {
  int num_lines_to_keep = 0;

  for (int i = 0; i < num_lines; i++) {
    char *line = lines[i];

    if (line[position] != char_to_drop) {
      lines[num_lines_to_keep++] = line;
    }
  }

  for (int i = num_lines_to_keep; i < num_lines; i++) {
    lines[i] = NULL;
  }

  struct LineList ll;
  ll.lines = lines;
  ll.length = num_lines_to_keep;

  return ll;
}

char** _dup_arr(char **lines, int num_lines) {
  int line_length = strlen(lines[0]);
  int total_size = sizeof(char) * line_length * num_lines;
  char **new_arr = (char**)malloc(total_size);

  for (int i = 0; i < num_lines; i++) {
    new_arr[i] = strdup(lines[i]);
  }

  return new_arr;
}

int _calculate_oxygen_generator_rating(char **lines, int num_lines) {
  lines = _dup_arr(lines, num_lines);
  int position = 0;
  int line_length = strlen(lines[0]);
  struct LineList line_list = {lines, num_lines};

  while (line_list.length > 1 && position < line_length) {
    int ones = 0;
    int zeroes = 0;

    for (int i = 0; i < line_list.length; i++) {
      char ch = line_list.lines[i][position];
      ch == '1' ? ones++ : zeroes++;
    }

    if (zeroes > ones) {
      line_list = _drop_lines_with_ch_at_pos(line_list.lines, line_list.length, position, '1');
    } else {
      line_list = _drop_lines_with_ch_at_pos(line_list.lines, line_list.length, position, '0');
    }

    position++;
  }

  return strtol(line_list.lines[0], NULL, 2);
}

int _calculate_co2_scrubber_rating(char **lines, int num_lines) {
  lines = _dup_arr(lines, num_lines);
  int position = 0;
  int line_length = strlen(lines[0]);
  struct LineList line_list = {lines, num_lines};

  while (line_list.length > 1 && position < line_length) {
    int ones = 0;
    int zeroes = 0;

    for (int i = 0; i < line_list.length; i++) {
      char ch = line_list.lines[i][position];
      ch == '1' ? ones++ : zeroes++;
    }

    if (zeroes < ones) {
      line_list = _drop_lines_with_ch_at_pos(line_list.lines, line_list.length, position, '1');
    } else if (ones < zeroes) {
      line_list = _drop_lines_with_ch_at_pos(line_list.lines, line_list.length, position, '0');
    } else {
      line_list = _drop_lines_with_ch_at_pos(line_list.lines, line_list.length, position, '1');
    }

    position++;
  }

  return strtol(line_list.lines[0], NULL, 2);
}

void run3_2(char *input) {
  char *file_contents = _load_file(input);
  int num_lines = _num_lines(file_contents);
  char **lines = _split_lines(file_contents, num_lines);

  int oxygen_rating = _calculate_oxygen_generator_rating(lines, num_lines);
  int co2_rating = _calculate_co2_scrubber_rating(lines, num_lines);

  printf("Oxygen generator rating: %d\n", oxygen_rating);
  printf("CO2 scrubber rating: %d\n", co2_rating);
  printf("Life support raiting: %d\n", oxygen_rating * co2_rating);
}
