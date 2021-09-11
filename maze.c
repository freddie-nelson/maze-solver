#include <stdlib.h>
#include <stdbool.h>

struct Cell
{
  bool visited;
  bool l;
  bool r;
  bool t;
  bool b;
  unsigned x;
  unsigned y;
};

typedef struct Maze
{
  struct Cell *cells;
  unsigned width;
  unsigned height;
};

struct Maze *newMaze(unsigned w, unsigned h)
{
  struct Maze *m = (struct Maze *)malloc(sizeof(struct Maze));

  struct Cell *cells[h];
  for (size_t i = 0; i < h; i++)
  {
    cells[i] = (struct Cell *)malloc(w * sizeof(struct Cell));

    for (size_t j = 0; j < w; j++)
    {
      cells[i][j].x = j;
      cells[i][j].y = i;
    }
  }

  m->cells = (struct Cell *)cells;

  m->width = w;
  m->height = h;

  return m;
}