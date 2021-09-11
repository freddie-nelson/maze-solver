#ifndef MAZEH
#define MAZEH

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "algorithms.h"

typedef struct Cell
{
  bool visited;
  bool l;
  bool r;
  bool t;
  bool b;
  unsigned x;
  unsigned y;
} Cell;

typedef struct Maze
{
  Cell *cells;
  unsigned width;
  unsigned height;
} Maze;

unsigned getIndex(Maze *m, unsigned x, unsigned y);

struct Maze *newMaze(unsigned w, unsigned h);
void generateMaze(Maze *m, enum Algorithms algo);
void drawMaze(Maze *m, SDL_Renderer *renderer);

#endif