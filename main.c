#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NO_ROWS 10
#define NO_COLS 20

// Analogous to the following shell cmd:
// $ clear
void clearPrint() {
  printf("\033[2J\033[1;1H");
}

int** createWorld(int rows, int cols) {
  // Create the row pointers
  /*
    row 0 -> null
    row 1 -> null
    row 2 -> null
    ...
  */
  int **world = malloc(rows * sizeof(int *));

  // Create the contents of each row
  /*
    row 0 -> [0, 0, 0, ...]
    row 1 -> [0, 0, 0, ...]
    row 2 -> [0, 0, 0, ...]
  */
  for (int i = 0; i < rows; i++) {
    world[i] = calloc(cols, sizeof(int));
  }

  return world;
}

void printWorld(int **world, int rows, int cols) {
  // Iterate through each row
  for (int i = 0; i < rows; i++) {
    // Print each row (iterate through each column)
    for (int j = 0; j < cols; j++) {
      printf("%d ", world[i][j]);
    }
    printf("\n");
  }
}

void freeWorld(int **world, int rows) {
  // Free each row
  for (int i = 0; i < rows; i++) {
    free(world[i]);
  }

  // Free the pointer to the rows
  free(world);
}

bool isValidIndex(int currRow, int currCol, int rows, int cols) {
  return currRow >= 0
      && currCol >= 0
      && currRow < rows
      && currCol < cols;
}

int isOne(int **world, int currRow, int currCol, int rows, int cols) {
  if (isValidIndex(currRow, currCol, rows, cols)) {
    return world[currRow][currCol];
  } else {
    return 0;
  }
}

int noAdjacentOnes(int **world, int currRow, int currCol, int rows, int cols) {
  int sum = 0;

  sum += isOne(world, currRow - 1, currCol - 1, rows, cols)
       + isOne(world, currRow - 1, currCol    , rows, cols)
       + isOne(world, currRow - 1, currCol + 1, rows, cols)
       + isOne(world, currRow    , currCol - 1, rows, cols)
       + isOne(world, currRow    , currCol + 1, rows, cols)
       + isOne(world, currRow + 1, currCol - 1, rows, cols)
       + isOne(world, currRow + 1, currCol    , rows, cols)
       + isOne(world, currRow + 1, currCol + 1, rows, cols);

  return sum;
}

// Perform 1 iteration of Conway's Game of Life
int** iterGameOfLife(int **currWorld, int rows, int cols) {
  int **nextWorld = createWorld(rows, cols);

  // Update next world by scanning through current world
  /*
         j0j1j2j3j4j5
       + - - - - - -
    i0 | 0 0 0 0 0 0
    i1 | 0 0 0 1 0 0   <-- 1 is at row 1, col 3 (0-index)
    i2 | 0 0 0 0 0 0
  */
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int energy = noAdjacentOnes(currWorld, i, j, rows, cols);

      // Explicit rules of Conway's Game of Life:
      /*
        Any live cell with two or three live neighbours survives.
        Any dead cell with three live neighbours becomes a live cell.
        All other cells die / remain dead.
        (Wikipedia)
      */
      if (currWorld[i][j] == 1) {
        nextWorld[i][j] = (energy == 2 || energy == 3);
      } else {
        nextWorld[i][j] = (energy == 3);
      }
    }
  }

  // Next world is now current world, and current world is now previous world
  // So we free this world
  freeWorld(currWorld, rows);
  return nextWorld;
}

int** run(int **world, int rows, int cols) {
  while (true) {
    // Print world
    clearPrint();
    printWorld(world, rows, cols);
    printf("[Enter] to continue, [s] to stop\n");
    // Wait until key pressed
    char c = getchar();
    if (c == 's') {
      break;
    }

    // Perform next iteration
    world = iterGameOfLife(world, rows, cols);
  }

  return world;
}

int main(void) {
  int **world = createWorld(NO_ROWS, NO_COLS);
  world[0][2] = 1;
  world[1][0] = 1;
  world[1][2] = 1;
  world[2][1] = 1;
  world[2][2] = 1;

  /*
    Unexpected:
    Original function was void run(int **world, ...)
    But world in main does not get updated
    (and I want to free world in main)
  */
  world = run(world, NO_ROWS, NO_COLS);

  freeWorld(world, NO_ROWS);
  return 0;
}
