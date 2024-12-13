#include <gtest/gtest.h>

extern "C" {
  #include "./part1.h"
  #include "./part2.h"
}

char** test_lines() {
  int line_length = 2;
  int number_of_lines = 4;
  int total_size = sizeof(char) * line_length * number_of_lines;
  char **lines = (char**)malloc(total_size);
  lines[0] = (char*)"00";
  lines[1] = (char*)"01";
  lines[2] = (char*)"10";
  lines[3] = (char*)"11";
  return lines;
}

TEST(calculate_gamma, all_zero) {
  struct Column col1;
  col1.position = 0;
  col1.zeroes = 1;
  col1.ones = 0;
  struct Column col2;
  col2.position = 1;
  col2.zeroes = 1;
  col2.ones = 0;
  struct Column cols[] = {col1, col2};

  char *gamma = _calculate_gamma(cols, 2);

  EXPECT_STREQ(gamma, "00");
}

TEST(calculate_gamma, all_one) {
  struct Column col1;
  col1.position = 0;
  col1.zeroes = 0;
  col1.ones = 1;
  struct Column col2;
  col2.position = 1;
  col2.zeroes = 0;
  col2.ones = 1;
  struct Column cols[] = {col1, col2};

  char *gamma = _calculate_gamma(cols, 2);

  EXPECT_STREQ(gamma, "11");
}

TEST(calculate_epsilon, all_zero) {
  struct Column col1;
  col1.position = 0;
  col1.zeroes = 1;
  col1.ones = 0;
  struct Column col2;
  col2.position = 1;
  col2.zeroes = 1;
  col2.ones = 0;
  struct Column cols[] = {col1, col2};

  char *epsilon = _calculate_epsilon(cols, 2);

  EXPECT_STREQ(epsilon, "11");
}

TEST(calculate_epsilon, all_one) {
  struct Column col1;
  col1.position = 0;
  col1.zeroes = 0;
  col1.ones = 1;
  struct Column col2;
  col2.position = 1;
  col2.zeroes = 0;
  col2.ones = 1;
  struct Column cols[] = {col1, col2};

  char *epsilon = _calculate_epsilon(cols, 2);

  EXPECT_STREQ(epsilon, "00");
}

TEST(_drop_lines_with_ch_at_pos, removes_lines_at_pos_0) {
  char **lines = test_lines();

  struct LineList ll = _drop_lines_with_ch_at_pos(lines, 4, 0, '0');

  char **result = ll.lines;
  EXPECT_STREQ(result[0], "10");
  EXPECT_STREQ(result[1], "11");
}

TEST(_drop_lines_with_ch_at_pos, removes_lines_at_pos_1) {
  char **lines = test_lines();

  struct LineList ll = _drop_lines_with_ch_at_pos(lines, 4, 1, '0');

  char **result = ll.lines;
  EXPECT_STREQ(result[0], "01");
  EXPECT_STREQ(result[1], "11");
}

TEST(_drop_lines_with_ch_at_pos, returns_length) {
  char **lines = test_lines();

  struct LineList ll = _drop_lines_with_ch_at_pos(lines, 4, 0, '0');

  EXPECT_EQ(ll.length, 2);
}
