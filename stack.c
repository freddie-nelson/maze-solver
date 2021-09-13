#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze.h"

// A structure to represent a stack
typedef struct Stack
{
  int top;
  unsigned capacity;
  Cell **array;
} Stack;

// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack *createStack(unsigned capacity)
{
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = malloc(stack->capacity * sizeof(Cell));
  return stack;
}

// Stack is full when top is equal to the last index
bool isFull(Stack *stack)
{
  return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
bool isEmpty(Stack *stack)
{
  return stack->top == -1;
}

// Function to add an item to stack.  It increases top by 1
void push(Stack *stack, Cell *item)
{
  if (isFull(stack))
    return;

  stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
Cell *pop(Stack *stack)
{
  if (isEmpty(stack))
    return NULL;
  return stack->array[stack->top--];
}

// Function to return the top from stack without removing it
Cell *peek(Stack *stack)
{
  if (isEmpty(stack))
    return NULL;
  return stack->array[stack->top];
}