#ifndef WORLD_PHYSICS_H
#define WORLD_PHYSICS_H
#include "util.h"
#include "world.h"

int isOne(int **world, int currRow, int currCol, int rows, int cols);
int noAdjacentOnes(int **world, int currRow, int currCol, int rows, int cols);
int** iterGameOfLife(int **currWorld, int rows, int cols);

#endif
