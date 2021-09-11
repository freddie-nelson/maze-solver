#ifndef MAZEH
#define MAZEH

#include <stdlib.h>
#include <stdbool.h>

struct Cell;
typedef struct Maze;

struct Maze *newMaze(unsigned w, unsigned h);

#endif