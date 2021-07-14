#include "world_physics.h"

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
