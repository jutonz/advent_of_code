#include <gtest/gtest.h>

extern "C" {
  #include "helpers.h"
}

#define SENTINEL -1

TEST(initialize_window, sets_values_to_sentinel) {
  static const int WINDOW_SIZE = 3;
  int window[WINDOW_SIZE];

  initialize_window(window, WINDOW_SIZE);

  for(int i = 0; i < WINDOW_SIZE; i++) {
    EXPECT_EQ(window[i], SENTINEL);
  }
}

TEST(add_to_window, replaces_first_sentinel) {
  static const int WINDOW_SIZE = 2;
  int window[WINDOW_SIZE];
  initialize_window(window, WINDOW_SIZE);
  const int value = 42;

  add_to_window(window, WINDOW_SIZE, value);

  EXPECT_EQ(window[0], value);
  EXPECT_EQ(window[1], SENTINEL);
}

TEST(add_to_window, replaces_last_sentinel) {
  static const int WINDOW_SIZE = 2;
  int window[WINDOW_SIZE];
  initialize_window(window, WINDOW_SIZE);

  add_to_window(window, WINDOW_SIZE, 1);
  add_to_window(window, WINDOW_SIZE, 2);

  EXPECT_EQ(window[0], 1);
  EXPECT_EQ(window[1], 2);
}

TEST(add_to_window, shifts_window) {
  static const int WINDOW_SIZE = 2;
  int window[] = {1, 2};

  add_to_window(window, WINDOW_SIZE, 3);

  EXPECT_EQ(window[0], 2);
  EXPECT_EQ(window[1], 3);
}

TEST(sum_window, sums_contents) {
  int window[] = {1, 2, 3};

  int sum = sum_window(window, 3);

  EXPECT_EQ(sum, 6);
}
