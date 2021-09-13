#ifndef STACKH
#define STACKH

#include <stdbool.h>
#include "maze.h"

typedef struct Stack
{
  int top;
  unsigned capacity;
  Cell **array;
} Stack;

Stack *createStack(unsigned capacity);

bool isFull(Stack *stack);
bool isEmpty(Stack *stack);

void push(Stack *stack, Cell *item);
Cell *pop(Stack *stack);
Cell *peek(Stack *stack);

#endif