//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>

extern "C" {
  #include "./day3/part1.h"
  #include "./day3/part2.h"
}

#include "./day4/part1.h"
#include "./day4/part2.h"

using std::cout;

void print_usage() {
  printf("Usage: ./advent -d[day] -p[part] path/to/input.txt\n");
}

void assert_args(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s -d[day] -p[part] path/to/input.txt\n", argv[0]);
    exit(1);
  }
}

int extract_day(char *input) {
  int day = -1;
  sscanf(input, "-d%d", &day);

  if (day < 1) {
    print_usage();
    exit(1);
  }

  return day;
}

int extract_part(char *input) {
  int part = -1;
  sscanf(input, "-p%d", &part);

  if (part < 1) {
    print_usage();
    exit(1);
  }

  return part;
}

void not_implemented(int day, int part) {
  printf("Day %d, part %d is not implemented yet\n", day, part);
  exit(1);
}

int main(int argc, char *argv[]) {
  assert_args(argc, argv);
  int day = extract_day(argv[1]);
  int part = extract_part(argv[2]);
  char *input = argv[3];

  switch(day) {
    case 3:
      part == 1 ? run3_1(input) : run3_2(input);
      break;
    case 4:
      part == 1 ? run4_1(input) : run4_2(input);
      break;
    default:
      not_implemented(day, part);
  }

  return 0;
}
