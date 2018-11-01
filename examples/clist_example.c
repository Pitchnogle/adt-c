/**
@file clist_example.c
@brief 
Example usage of circular linked-list ADT

@author Justin Hadella (pitchnogle@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>

#include "clist.h"

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------

static void print_clist(const CList_t *list);

// =============================================================================
// Main Program
// =============================================================================

int main(int argc, char *argv[])
{
  CList_t list;
  CList_Element_t *element;

  int *data;
  int i;

  // Initialize the circular linked-list
  clist_init(&list, free);

  // Perform some circular list operations
  element = clist_head(&list);

  for (i = 0; i < 10; i++) {
    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return 1;

    *data = i + 1;

    if (clist_insert_next(&list, element, data) != 0)
        return 1;

    if (element == NULL)
        element = clist_next(clist_head(&list));
    else
        element = clist_next(element);
  }

  print_clist(&list);

  element = clist_head(&list);

  for (i = 0; i < 10; i++)
    element = clist_next(element);

  data = clist_data(element);
  fprintf(stdout, "Circling and removing an element after the one containing "
    "%03d\n",*data);

  if (clist_remove_next(&list, element, (void **)&data) != 0)
    return 1;

  free(data);
  print_clist(&list);

  element = clist_head(&list);

  for (i = 0; i < 15; i++)
    element = clist_next(element);

  data = clist_data(element);
  fprintf(stdout, "Circling and inserting 011 after the element containing "
    "%03d\n", *data);

  if ((data = (int *)malloc(sizeof(int))) == NULL)
    return 1;

  *data = 11;
  if (clist_insert_next(&list, element, data) != 0)
    return 1;

  print_clist(&list);

  // Destroy the linked list
  fprintf(stdout, "Destroying the list\n");
  clist_destroy(&list);

  return 0;
}

// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Local Functions
// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

static void print_clist(const CList_t *list)
{
  CList_Element_t *element;
  int *data;
  int size;
  int i;

  fprintf(stdout, "List size is %d (circling twice)\n", clist_size(list));

  size = clist_size(list);
  element = clist_head(list);

  i = 0;
  while (i < size * 2) {
   data = clist_data(element);
   fprintf(stdout, "list[%03d]=%03d\n", (i % size), *data);
   element = clist_next(element);
   i++;
  }
}
