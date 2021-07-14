#include "util.h"

// Analogous to the following shell cmd:
// $ clear
void clearPrint() {
  printf("\033[2J\033[1;1H");
}

bool isValidIndex(int currRow, int currCol, int rows, int cols) {
  return currRow >= 0
      && currCol >= 0
      && currRow < rows
      && currCol < cols;
}
