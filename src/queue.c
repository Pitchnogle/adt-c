/**
@file queue.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include "queue.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int queue_enqueue(Queue_t *queue, const void *data)
{
  return list_insert_next(queue, list_tail(queue), data);
}


int queue_dequeue(Queue_t *queue, void **data)
{
  return list_remove_next(queue, NULL, data);
}
