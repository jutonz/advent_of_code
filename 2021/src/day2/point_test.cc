#include <gtest/gtest.h>

extern "C" {
  #include "point.h"
}

TEST(navigate, goes_forward) {
  struct Point p = new_point();

  navigate(&p, (char*)"forward", 1);

  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 1);
}

TEST(navigate, goes_up) {
  struct Point p = new_point();

  navigate(&p, (char*)"up", 1);

  EXPECT_EQ(p.x, 1);
  EXPECT_EQ(p.y, 0);
}

TEST(navigate, goes_down) {
  struct Point p = new_point();

  navigate(&p, (char*)"down", 1);

  EXPECT_EQ(p.x, -1);
  EXPECT_EQ(p.y, 0);
}
