#ifndef POINT
#define POINT

struct Point {
  int x;
  int y;
};

void navigate(struct Point *p, char *direction, int amount);
struct Point new_point();

#endif
