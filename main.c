#include "util.h"
#include "world.h"
#include "world_physics.h"
#define NO_ROWS 10
#define NO_COLS 20

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
