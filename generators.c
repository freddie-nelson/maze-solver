#include <stdbool.h>
#include <SDL2/SDL.h>
#include "maze_helpers.h"
#include "stack.h"

void generateDepthFirst(Maze *m, Cell *entry)
{
  struct Stack *stack = createStack(m->width * m->height);

  entry->visited = true;
  push(stack, entry);

  while (!isEmpty(stack))
  {
    Cell *c = pop(stack);
    Cell **neighbours = malloc(4 * sizeof(Cell));
    unsigned numOfNeighbours = getNeighbours(m, c, neighbours);

    // printf("\n numOfN: %u, cellX: %u, cellY: %u, index: %u | ", numOfNeighbours, c->x, c->y, MAZE_INDEX(m, c->x, c->y));

    // get visitable neighbours
    Cell **visitable = malloc(numOfNeighbours * sizeof(Cell));
    unsigned curr = 0;
    for (size_t i = 0; i < numOfNeighbours; i++)
    {
      // printf(" neighbour[%u](x: %u, y: %u, visited: %u)", i, neighbours[i]->x, neighbours[i]->y, neighbours[i]->visited);
      if (!neighbours[i]->visited)
      {
        visitable[curr] = neighbours[i];
        curr++;
      }
    }

    // pick random neighbour to visit
    if (curr > 0)
    {
      unsigned vi = rand() % curr;
      Cell *chosen = visitable[vi];
      chosen->visited = true;

      // left
      if (chosen->x + 1 == c->x)
      {
        chosen->r = false;
        c->l = false;
      }
      // right
      else if (chosen->x - 1 == c->x)
      {
        chosen->l = false;
        c->r = false;
      }
      // top
      else if (chosen->y + 1 == c->y)
      {
        chosen->b = false;
        c->t = false;
      }
      // bottom
      else if (chosen->y - 1 == c->y)
      {
        chosen->t = false;
        c->b = false;
      }

      push(stack, c);
      push(stack, chosen);
    }
    // else
    // {
    //   printf(" BACKTRACKING %u, ", isEmpty(stack));
    // }
  }

  return;
}