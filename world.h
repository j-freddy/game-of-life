#ifndef WORLD_H
#define WORLD_H
#include <stdio.h>
#include <stdlib.h>

int** createWorld(int rows, int cols);
void printWorld(int **world, int rows, int cols);
void freeWorld(int **world, int rows);

#endif
