/**
@file list.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include <stdlib.h>
#include <string.h>

#include "list.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void list_init(List_t *list, void (*destroy)(void *data))
{
  // Initialize the list
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}


void list_destroy(List_t *list)
{
  void *data;

  // Remove each element in list
  while (list_size(list) > 0) {
    if (list_remove_next(list, NULL, (void**)&data) == 0 && list_destroy != NULL) {
      list->destroy(data);
    }
  }

  // No operations permitted at this point -- clear memory as precaution
  memset(list, 0, sizeof (List_t));
}


int list_insert_next(List_t *list, List_Element_t *element, const void *data)
{
  List_Element_t *new_element;

  // Allocate storage for the element
  if ((new_element = (List_Element_t *)malloc(sizeof (List_Element_t))) == NULL) {
    return -1;
  }

  // Insert the element into the linked-list
  new_element->data = (void *)data;
  
  if (element == NULL) {
    // Insert at head of the linked-list

    if (list_size(list) == 0)
      list->tail = new_element;

    new_element->next = list->head;
    list->head = new_element;
  }
  else {
    // Insert somewhere other than the head

    if (element->next == NULL)
      list->tail = new_element;

    new_element->next = element->next;
    element->next = new_element;
  }

  // Adjust the size
  list->size++;

  return 0;
}


int list_remove_next(List_t *list, List_Element_t *element, void **data)
{
  List_Element_t *old_element;

  // Check for empty list!
  if (list_size(list) == 0)
    return -1;

  if (element == NULL) {
    // Remove from the head of the linked-list

    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;

    if (list_size(list) == 1)
      list->tail = NULL;
  }
  else {
    // Remove from somewhere other than the head

    if (element->next == NULL)
      return -1;

    *data = element->next->data;
    old_element = element->next;
    element->next = element->next->next;

    if (element->next == NULL)
      list->tail = element;
  }

  // Free storage allocated by the abstract datatype
  free (old_element);

  // Adjust the size of the list
  list->size--;

  return 0;
}
