#ifndef MAZEH
#define MAZEH

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "maze_helpers.h"

unsigned getIndex(Maze *m, unsigned x, unsigned y);

struct Maze *newMaze(unsigned w, unsigned h);
void generateMaze(Maze *m, enum Algorithms algo);
void drawMaze(Maze *m, SDL_Renderer *renderer);

#endif