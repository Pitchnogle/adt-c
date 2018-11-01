/**
@file list.c

See header

@author Justin Hadella
*/

#include <stdlib.h>
#include <string.h>

#include "dlist.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void dlist_init(DList_t *list, void (*destroy)(void *data))
{
  // Initialize the list
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}


void dlist_destroy(DList_t *list)
{
  void *data;

  // Remove each element in list
  while (dlist_size(list) > 0) {
    if (dlist_remove(list, dlist_tail(list), (void**)&data) == 0 && list->destroy != NULL) {
      list->destroy(data);
    }
  }

  // No operations permitted a this point but clear memory as precaution
  memset(list, 0, sizeof (DList_t));
}


int dlist_insert_next(DList_t *list, DList_Element_t *element, const void *data)
{
  DList_Element_t *new_element;

  // Do not allow a NULL element unless the list is empty
  if (element == NULL && dlist_size(list) != 0)
    return -1;

  // Allocate storage for the element
  if ((new_element = (DList_Element_t *)malloc(sizeof (DList_Element_t))) == NULL) {
    return -1;
  }

  // Insert the element into the linked-list
  new_element->data = (void *)data;
  
  if (dlist_size(list) == 0) {
    // Insert into empty list

    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
  }
  else {
    // Insert into non-empty list

    new_element->next = element->next;
    new_element->prev = element;

    if (element->next == NULL)
      list->tail = new_element;
    else
      element->next->prev = new_element;

    element->next = new_element;
  }

  // Adjust the size
  list->size++;

  return 0;
}


int dlist_insert_prev(DList_t *list, DList_Element_t *element, const void *data)
{
  DList_Element_t *new_element;

  // Do not allow a NULL element unless the list is empty
  if (element == NULL && dlist_size(list) != 0)
    return -1;

  // Allocate storage for the element
  if ((new_element = (DList_Element_t *)malloc(sizeof (DList_Element_t))) == NULL) {
    return -1;
  }

  // Insert the element into the linked-list
  new_element->data = (void *)data;
  
  if (dlist_size(list) == 0) {
    // Insert into empty list

    list->head = new_element;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = new_element;
  }
  else {
    // Insert into non-empty list

    new_element->next = element;
    new_element->prev = element->prev;

    if (element->prev == NULL)
      list->head = new_element;
    else
      element->prev->next = new_element;

    element->prev = new_element;
  }

  // Adjust the size
  list->size++;

  return 0;
}


int dlist_remove(DList_t *list, DList_Element_t *element, void **data)
{
  // Do not allow a NULL element or removal from empty list
  if (element == NULL || dlist_size(list) == 0)
    return - 1;

  // Remove the element from the linked-list

  *data = element->data;

  if (element == list->head) {
    // Remove from the head of the list

    list->head = element->next;

    if (list->head == NULL)
      list->tail = NULL;
    else
      element->next->prev = NULL;
  }
  else {
    // Remove from somewhere but the head

    element->prev->next = element->next;

    if (element->next == NULL)
      list->tail = element->prev;
    else
      element->next->prev = element->prev;
  }

  // Free storage allocated by the abstract datatype
  free (element);

  // Adjust the size of the list
  list->size--;

  return 0;
}
