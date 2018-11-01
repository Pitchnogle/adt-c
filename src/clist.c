/**
@file clist.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include <stdlib.h>
#include <string.h>

#include "clist.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void clist_init(CList_t *list, void (*destroy)(void *data))
{
  // Initialize the list
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
}


void clist_destroy(CList_t *list)
{
  void *data;

  // Remove each element in list
  while (clist_size(list) > 0) {
    if (clist_remove_next(list, list->head, (void**)&data) == 0 && clist_destroy != NULL) {
      list->destroy(data);
    }
  }

  // No operations permitted at this point -- clear memory as precaution
  memset(list, 0, sizeof (CList_t));
}


int clist_insert_next(CList_t *list, CList_Element_t *element, const void *data)
{
  CList_Element_t *new_element;

  // Allocate storage for the element
  if ((new_element = (CList_Element_t *)malloc(sizeof (CList_Element_t))) == NULL) {
    return -1;
  }

  // Insert the element into the linked-list
  new_element->data = (void *)data;
  
  if (clist_size(list) == 0) {
    // Insert into empty list

    new_element->next = new_element;
    list->head = new_element;
  }
  else {
    // Insert into a non-empty list

    new_element->next = element->next;
    element->next = new_element;
  }

  // Adjust the size
  list->size++;

  return 0;
}


int clist_remove_next(CList_t *list, CList_Element_t *element, void **data)
{
  CList_Element_t *old_element;

  // Check for empty list!
  if (clist_size(list) == 0)
    return -1;

  *data = element->next->data;

  if (element->next == element) {
    // Remove the last element

    old_element = element->next;
    list->head = NULL;
  }
  else {
    // Remove an element other than the last element

    old_element = element->next;
    element->next = element->next->next;
    if (old_element == clist_head(list))
      list->head = old_element->next;
  }

  // Free storage allocated by the abstract datatype
  free (old_element);

  // Adjust the size of the list
  list->size--;

  return 0;
}
