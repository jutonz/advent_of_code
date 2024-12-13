#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

  FILE *fp = open_file(argv[1]);
  static const short BUFFER_LENGTH = 255;
  char buffer[BUFFER_LENGTH];

  bool initial = true;
  int previous, current;
  int increases = 0;
  while(fgets(buffer, BUFFER_LENGTH, fp)) {
    sscanf(buffer, "%d", &current);

    if (initial) {
      printf("%d (initial)\n", current);
    } else if (current > previous) {
      increases++;
      printf("%d (increase)\n", current);
    } else if (current < previous) {
      printf("%d (decrease)\n", current);
    } else {
      printf("%d (no change)\n", current);
    }

    initial = false;
    previous = current;
  }

  printf("There were %d increases\n", increases);
  fclose(fp);

  return 0;
}
