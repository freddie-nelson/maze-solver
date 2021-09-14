#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "maze_helpers.h"

typedef struct Step
{
  struct Step *prev;
  Cell *c;
} Step;

// path is implemented as a queue
typedef struct Path
{
  int front, rear, size;
  unsigned capacity;
  Step **array;
} Path;

Path *createPath(unsigned capacity)
{
  Path *p = (Path *)malloc(sizeof(Path));
  p->capacity = capacity;
  p->front = p->size = 0;

  p->rear = capacity - 1;
  p->array = (Step **)malloc(p->capacity * sizeof(Step));
  return p;
}

bool isPathFull(Path *p)
{
  return (p->size == p->capacity);
}

bool isPathEmpty(Path *p)
{
  return (p->size == 0);
}

void addPath(Path *p, Step *s)
{
  if (isPathFull(p))
    return;
  p->rear = (p->rear + 1) % p->capacity;
  p->array[p->rear] = s;
  p->size = p->size + 1;
}

Step *removeStep(Path *p)
{
  if (isPathEmpty(p))
    return NULL;
  Step *s = p->array[p->front];
  p->front = (p->front + 1) % p->capacity;
  p->size = p->size - 1;
  return s;
}

Step *front(Path *p)
{
  if (isPathEmpty(p))
    return NULL;
  return p->array[p->front];
}

Step *rear(Path *p)
{
  if (isPathEmpty(p))
    return NULL;
  return p->array[p->rear];
}