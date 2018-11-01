/** 
@file list.h
@brief 
Definitions of a generic linked-list ADT

@note
Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)

@author Justin Hadella (pitchnogle@gmail.com)
*/
#ifndef LIST_h
#define LIST_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

/**
@struct List_Element_t
Generic linked-list element
*/
typedef struct List_Element_T {
  void *data;                  ///< Pointer to data
  struct List_Element_T *next; ///< Pointer to next element in list

} List_Element_t;

/**
@struct List_t
Generic linked-list
*/
typedef struct List_T {
  int size; ///< Number of elements in list

  int (*match)(const void *a, const void *b);
  void (*destroy)(void *data);

  List_Element_t *head; ///< Pointer to first element in list
  List_Element_t *tail; ///< Pointer to last element in list

} List_t;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
Function to initialize a linked-list

@pre
Must be called before list can be used by any other operation

The _destroy_ argument provides a way to free dynamically allocated data when
*list_destroy* is called. For example, if the list contains data dynamically
allocated using _malloc_, _destroy_ should be set to _free_ to free the data as
the linked-list is destroyed. For a linked-list containing data that should not
be freed, _destroy_ should be set to NULL.

Complexity: O(1)

@param [out] *list     The linked-list to init
@param [in] (*destroy) Function pointer to free data element memory
*/
void list_init(List_t *list, void (*destroy)(void *data));

/**
Function to destroy a linked-list

The *list_destroy* operation removes all elements from a linked-list and calls
the function passed as _destroy_ to *list_init* once for each element as it is
removed, provided _destroy_ was not set to NULL.

@note
No operation is permitted after *list_destroy()* is called unless *list_init()*
is called again. 

Complexity: O(n)

@param [in,out] *list  The linked-list to destroy
*/
void list_destroy(List_t *list);

/**
Function to insert an element into a linked-list

Inserts an element just after _element_ into the linked-list. If _element_ is
NULL, the new element is inserted at the head of the list. The new element 
contains a pointer to _data_, so the memory referenced by _data_ should remain
valid as long as the element remains in the list.

Complexity: O(1)

@param [in,out] *list     The linked-list to insert element into
@param [in]     *element  Pointer to element to insert after
@param [in]     *data     The data to insert

@return 0 if inserting into list was successful, otherwise -1
*/
int list_insert_next(List_t *list, List_Element_t *element, const void *data);

/**
Function to remove an element from a linked list

Removes the element just past _element_ from the linked-list. If _element_ is
NULL, the element at the head of the list is removed. Upon return _data_ 
points to the data stored in the element that was removed.

Complexity: O(1)

@param [in,out] *list     The linked-list to destroy
@param [in]     *element  Pointer to element to remove after
@param [out]    **data    The data removed

@return 0 if inserting into list was successful, otherwise -1
*/
int list_remove_next(List_t *list, List_Element_t *element, void **data);

/**
MACRO that evaluates to the number of elements in the linked-list
*/
#define list_size(list) ((list)->size)

/**
MACRO that evaluates to the element at the head of a linked-list
*/
#define list_head(list) ((list)->head)

/**
MACRO that evaluates to the element at the tail of a linked-list
*/
#define list_tail(list) ((list)->tail)

/**
MACRO that determines whether element is the head of linked-list
*/
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

/**
MACRO that determines whether element is the tail of linked-list
*/
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

/**
MACRO that evaluates to the data stored in given element of a linked-list
*/
#define list_data(element) ((element)->data)

/**
MACRO that evaluates to the next element given an element in a linked-list
*/
#define list_next(element) ((element)->next)

#ifdef __cplusplus
}
#endif
#endif // LIST_h
