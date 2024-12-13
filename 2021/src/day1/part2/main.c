#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

FILE* open_file(const char *filename) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    perror("Could not open file\n");
    exit(1);
  }

  return fp;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    char error[256];
    snprintf(error, 256, "Usage: %s /path/to/input.txt", argv[0]);
    printf("%s\n", error);
    exit(1);
  }

  static const int WINDOW_SIZE = 3;
  int window[WINDOW_SIZE];
  int linesSeen = 0;
  initialize_window(window, WINDOW_SIZE);

  FILE *fp = open_file(argv[1]);
  int value, currentSum, previousSum;
  int increases = 0;
  static const short BUFFER_LENGTH = 255;
  char buffer[BUFFER_LENGTH];
  while(fgets(buffer, BUFFER_LENGTH, fp)) {
    sscanf(buffer, "%d", &value);
    add_to_window(window, WINDOW_SIZE, value);
    linesSeen++;

    if (linesSeen <= WINDOW_SIZE) {
      printf("Value: %d (not enough data to calculate increase)\n", value);
      continue;
    }

    currentSum = sum_window(window, WINDOW_SIZE);

    printf("Value: %d; Sum: %d ", value, currentSum);

    if (!previousSum) {
      printf("(no previous sum)\n");
    } else if (currentSum > previousSum) {
      printf("(increase)\n");
      increases++;
    } else if (currentSum < previousSum) {
      printf("(decrease)\n");
    } else {
      printf("(no change)\n");
    }

    previousSum = currentSum;
  }

  printf("There were %d increases\n", increases);

  return 0;
}
