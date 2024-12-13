#include <stdio.h>
#include <stdlib.h>
#include "file.h"

FILE* open_file(const char *filename) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    perror("Could not open file\n");
    exit(1);
  }

  return fp;
}

char* check_args(int argc, char *argv[]) {
  if (argc != 2) {
    char error[256];
    snprintf(error, 256, "Usage: %s /path/to/input.txt", argv[0]);
    printf("%s\n", error);
    exit(1);
  }

  return argv[1];
}

static const short BUFFER_LENGTH = 255;
void read_file(char *filename, each_line_t each_line) {
  char buffer[BUFFER_LENGTH];
  FILE *fp = open_file(filename);

  while(fgets(buffer, BUFFER_LENGTH, fp)) {
    each_line(buffer);
  }
}
