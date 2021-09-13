#ifndef MAZEHELPERSH
#define MAZEHELPERSH

#include <stdbool.h>

#define MAZE_INDEX(m, x, y) ((y) * (m->height)) + (x)

enum Algorithms
{
  DEPTH_FIRST
};

typedef struct Cell
{
  bool visited;
  bool l;
  bool r;
  bool t;
  bool b;
  int x;
  int y;
} Cell;

typedef struct Maze
{
  Cell *cells;
  int width;
  int height;
} Maze;

#endif
