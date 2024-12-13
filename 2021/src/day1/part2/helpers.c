#define SENTINEL -1

void initialize_window(int *window, int size) {
  for (int i = 0; i < size; i++) {
    window[i] = SENTINEL;
  }
}

void add_to_window(int *window, int windowSize, int value) {
  // If any sentinels remaining, replace with actual value
  for (int i = 0; i < windowSize; i++) {
    if (window[i] == SENTINEL) {
      window[i] = value;
      return;
    }
  }

  // Shift all values one to the left
  for (int i = 0; i < windowSize - 1; i++) {
    window[i] = window[i + 1];
  }

  // Insert new value at end of window
  window[windowSize - 1] = value;
}

int sum_window(int *window, int windowSize) {
  int sum = 0;

  for (int i = 0; i < windowSize; i++) {
    sum += window[i];
  }

  return sum;
}
