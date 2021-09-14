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
  bool explored;
  bool path;
} Cell;

typedef struct Maze
{
  Cell *cells;
  int width;
  int height;
} Maze;

// get horizontal and vertical neighbours of provided cell
// neighbours order is [top, right, bottom, left]
// @returns the number of Cells in neighbours (max 4)
static unsigned getNeighbours(Maze *m, Cell *c, Cell **neighbours)
{
  unsigned size = 0;

  // top
  if (c->y - 1 >= 0)
  {
    neighbours[size] = &m->cells[MAZE_INDEX(m, c->x, c->y - 1)];
    size++;
  }

  // right
  if (c->x + 1 < m->width)
  {
    neighbours[size] = &m->cells[MAZE_INDEX(m, c->x + 1, c->y)];
    size++;
  }

  // bottom
  if (c->y + 1 < m->height)
  {
    neighbours[size] = &m->cells[MAZE_INDEX(m, c->x, c->y + 1)];
    size++;
  }

  // left
  if (c->x - 1 >= 0)
  {
    neighbours[size] = &m->cells[MAZE_INDEX(m, c->x - 1, c->y)];
    size++;
  }

  return size;
}

#endif
