/**
@file stack.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include "stack.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int stack_push(Stack_t *stack, const void *data)
{
  return list_insert_next(stack, NULL, data);
}


int stack_pop(Stack_t *stack, void **data)
{
  return list_remove_next(stack, NULL, data);
}
