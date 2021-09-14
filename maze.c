#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "globals.h"
#include "maze_helpers.h"
#include "generators.h"

Maze *newMaze(unsigned w, unsigned h)
{
  Maze *m = (Maze *)malloc(sizeof(Maze));

  m->width = w;
  m->height = h;

  m->cells = malloc(sizeof(Cell) * w * h);
  for (size_t i = 0; i < h; i++)
  {
    for (size_t j = 0; j < w; j++)
    {
      unsigned index = MAZE_INDEX(m, j, i);
      m->cells[index].x = j;
      m->cells[index].y = i;
      m->cells[index].visited = false;
      m->cells[index].b = true;
      m->cells[index].t = true;
      m->cells[index].r = true;
      m->cells[index].l = true;

      // printf(" x: %u, y: %u \n", m->cells[index].x, m->cells[index].y);
    }
  }

  return m;
}

void generateMaze(Maze *m, enum Algorithms algo)
{
  switch (algo)
  {
  case DEPTH_FIRST:
    generateDepthFirst(m, &m->cells[MAZE_INDEX(m, 0, 0)]);
    break;

  default:
    break;
  }
}

void drawMaze(Maze *m, SDL_Renderer *renderer)
{

  // calculate cell and wall dimensions
  const float CELL_WIDTH = (float)SCREEN_SIZE / (m->width * 2 + 1);
  const float CELL_HEIGHT = (float)SCREEN_SIZE / (m->height * 2 + 1);
  // printf(" w: %f ", CELL_WIDTH);

  for (size_t r = 0; r < m->height; r++)
  {
    for (size_t c = 0; c < m->width; c++)
    {
      Cell cell = m->cells[MAZE_INDEX(m, c, r)];
      // printf(" %u ", MAZE_INDEX(m, c, r));

      // set draw color
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      // draw non visited cells
      SDL_FRect *cellRect = malloc(sizeof(SDL_FRect));
      cellRect->x = c * (CELL_WIDTH * 2) + CELL_WIDTH;
      cellRect->y = r * (CELL_HEIGHT * 2) + CELL_HEIGHT;
      if (!cell.visited)
      {
        cellRect->h = CELL_HEIGHT;
        cellRect->w = CELL_WIDTH;
        SDL_RenderFillRectF(renderer, cellRect);
      }

      // printf(" x: %u, y: %u \n", cell.x, cell.y);

      // draw walls
      for (size_t i = 0; i < 8; i++)
      {
        bool wall = false;
        float x = cellRect->x;
        float y = cellRect->y;

        switch (i)
        {
        case 0:
          wall = cell.t;
          y -= CELL_HEIGHT;
          break;
        case 1:
          wall = cell.r;
          x += CELL_WIDTH;
          break;
        case 2:
          wall = cell.b;
          y += CELL_HEIGHT;
          break;
        case 3:
          wall = cell.l;
          x -= CELL_WIDTH;
          break;

        // diagonal walls
        case 4:
          wall = true;
          y -= CELL_HEIGHT;
          x -= CELL_WIDTH;
          break;
        case 5:
          wall = true;
          y -= CELL_HEIGHT;
          x += CELL_WIDTH;
          break;
        case 6:
          wall = true;
          y += CELL_HEIGHT;
          x -= CELL_WIDTH;
          break;
        case 7:
          wall = true;
          y += CELL_HEIGHT;
          x += CELL_WIDTH;
          break;
        default:
          break;
        }

        if (wall)
        {
          // draw wall
          SDL_FRect *wallRect = malloc(sizeof(SDL_FRect));
          wallRect->h = CELL_HEIGHT;
          wallRect->w = CELL_WIDTH;
          wallRect->x = x;
          wallRect->y = y;
          SDL_RenderFillRectF(renderer, wallRect);
          free(wallRect);
        }
      }

      free(cellRect);
    }
  }
}