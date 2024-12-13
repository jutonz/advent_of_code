#ifndef DAY3_1
#define DAY3_1

struct Column {
  int position;
  int zeroes;
  int ones;
};

char* _calculate_gamma(struct Column *cols, int length);
char* _calculate_epsilon(struct Column *cols, int length);
void run3_1(char*);

#endif
