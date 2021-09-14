#ifndef PATHH
#define PATHH

#include <stdbool.h>
#include "maze_helpers.h"

typedef struct Step
{
  struct Step *prev;
  Cell *c;
} Step;

typedef struct Path
{
  int front, rear, size;
  unsigned capacity;
  Step **array;
} Path;

Path *createPath(unsigned capacity);

bool isPathFull(Path *p);
bool isPathEmpty(Path *p);

void addPath(Path *p, Step *s);
Step *removeStep(Path *p);

Step *front(Path *p);
Step *rear(Path *p);

#endif