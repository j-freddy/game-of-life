#include "world.h"

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
