/**
@file stack_example.c
@brief 
Example usage of stack ADT

@author Justin Hadella (pitchnogle@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "list.h"

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------

static void print_stack(const Stack_t *stack);

// =============================================================================
// Main Program
// =============================================================================

int main(int argc, char *argv[])
{
  Stack_t stack;
  int *data;
  int i;

  // Initialize the stack
  stack_init(&stack, free);

  // Perform some stack operations
  fprintf(stdout, "Pushing 10 elements\n");

  for (i = 0; i < 10; i++) {
    if ((data = (int *)malloc(sizeof(int))) == NULL)
      return 1;

    *data = i + 1;

    if (stack_push(&stack, data) != 0)
      return 1;
  }

  print_stack(&stack);

  fprintf(stdout, "Popping 5 elements\n");

  for (i = 0; i < 5; i++) {
    if (stack_pop(&stack, (void **)&data) == 0)
      free(data);
    else
      return 1;
  }

  print_stack(&stack);

  fprintf(stdout, "Pushing 100 and 200\n");

  if ((data = (int *)malloc(sizeof(int))) == NULL)
    return 1;

  *data = 100;

  if (stack_push(&stack, data) != 0)
    return 1;

  if ((data = (int *)malloc(sizeof(int))) == NULL)
    return 1;

  *data = 200;

  if (stack_push(&stack, data) != 0)
    return 1;

  print_stack(&stack);

  if ((data = stack_peek(&stack)) != NULL)
    fprintf(stdout, "Peeking at the top element...Value=%03d\n", *data);
  else
    fprintf(stdout, "Peeking at the top element...Value=NULL\n");

  print_stack(&stack);

  fprintf(stdout, "Popping all elements\n");

  while (stack_size(&stack) > 0) {
    if (stack_pop(&stack, (void **)&data) == 0)
      free(data);
  }

  if ((data = stack_peek(&stack)) != NULL)
    fprintf(stdout, "Peeking at an empty stack...Value=%03d\n", *data);
  else
    fprintf(stdout, "Peeking at an empty stack...Value=NULL\n");

  print_stack(&stack);

  // Destroy the stack
  fprintf(stdout, "Destroying the stack\n");
  stack_destroy(&stack);

  return 0;
}

// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Local Functions
// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

static void print_stack(const Stack_t *stack)
{
  List_Element_t *element;
  int *data;
  int size;
  int i;

  // Display the stack
  fprintf(stdout, "Stack size is %d\n", size = stack_size(stack));

  i = 0;
  element = list_head(stack);

  while (i < size) {
    data = list_data(element);
    fprintf(stdout, "stack[%03d]=%03d\n", i, *data);
    element = list_next(element);
    i++;
  }
}
