#include <stdio.h>
#include <stdlib.h>
#include "../file.h"
#include "point.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    char error[256];
    snprintf(error, 256, "Usage: %s /path/to/input.txt", argv[0]);
    printf("%s\n", error);
    exit(1);
  }

  FILE *fp = open_file(argv[1]);
  static const short BUFFER_LENGTH = 255;
  char buffer[BUFFER_LENGTH];

  char direction[255];
  int amount;
  struct Point point;
  point.x = 0;
  point.y = 0;
  while(fgets(buffer, BUFFER_LENGTH, fp)) {
    sscanf(buffer, "%s %d\n", direction, &amount);
    navigate(&point, direction, amount);
    printf("Direction: %s; Amount: %d; x %d; y %d\n", direction, amount, point.x, point.y);
  }

  printf("Position is %d x %d\n", point.x, point.y);
  printf("Multiplied, that's %d\n", point.x * point.y);

  return 0;
}
