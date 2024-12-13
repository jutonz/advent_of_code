#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../file.h"
#include "./part1.h"

char* _calculate_gamma(struct Column *cols, int length) {
  char *gamma = (char*)malloc(sizeof(char) * (length + 1));
  gamma[length] = '\0';

  for (int i = 0; i < length; i++) {
    struct Column col = cols[i];
    gamma[i] = col.zeroes > col.ones ? '0' : '1';
  }

  return gamma;
}

char* _calculate_epsilon(struct Column *cols, int length) {
  char *epsilon = (char*)malloc(sizeof(char) * (length + 1));
  epsilon[length] = '\0';

  for (int i = 0; i < length; i++) {
    struct Column col = cols[i];
    epsilon[i] = col.zeroes < col.ones ? '0' : '1';
  }

  return epsilon;
}

static const short BUFFER_LENGTH = 255;

void run3_1(char *input_filename) {
  char buffer[BUFFER_LENGTH];
  FILE *fp = open_file(input_filename);

  bool first_line = true;
  struct Column *columns;
  int length;

  while(fgets(buffer, BUFFER_LENGTH, fp)) {
    if (first_line) {
      length = strlen(buffer) - 1;
      columns = (struct Column*)malloc(sizeof(struct Column) * length);
      for(int i = 0; i < length; i++) {
        struct Column column = {i, 0, 0};
        columns[i] = column;
      }
      first_line = false;
    }

    for (int i = 0; i < length; i++) {
      char ch = buffer[i];
      if (ch == '0') {
        columns[i].zeroes++;
      } else {
        columns[i].ones++;
      }
    }
  }

  char *gamma = _calculate_gamma(columns, length);
  char *epsilon = _calculate_epsilon(columns, length);

  int gamma_i = strtol(gamma, NULL, 2);
  int epsilon_i = strtol(epsilon, NULL, 2);

  printf("gamma: %d; epsilon: %d\n", gamma_i, epsilon_i);
  printf("Power consumption rating: %d\n", gamma_i * epsilon_i);
}
