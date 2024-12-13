#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file.h"
#include "./point.h"

void each_line(char *line) {
  static struct Point point = {0, 0};
  static int aim = 0;
  char direction[64];
  int amount;
  sscanf(line, "%s %d\n", direction, &amount);

  if (strcmp(direction, "forward") == 0) {
    point.x += amount;
    point.y += (amount * aim);
  } else if (strcmp(direction, "up") == 0) {
    aim -= amount;
  } else if (strcmp(direction, "down") == 0) {
    aim += amount;
  }

  printf("Direction: %s; Amount: %d; x %d; y %d; aim: %d\n", direction, amount, point.x, point.y, aim);
}

int main(int argc, char *argv[]) {
  char *filename = check_args(argc, argv);
  read_file(filename, &each_line);
  return 0;
}
