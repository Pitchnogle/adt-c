/** 
@file dlist.h
@brief 
Definitions of a generic doubly linked-list ADT

@note
Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)

@author Justin Hadella (pitchnogle@gmail.com)
*/
#ifndef DLIST_h
#define DLIST_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

/**
@struct DList_Element_t
Generic doubly linked-list element
*/
typedef struct DList_Element_T {
  void *data;                   ///< Pointer to data

  struct DList_Element_T *prev; ///< Pointer to prev element in list
  struct DList_Element_T *next; ///< Pointer to next element in list

} DList_Element_t;

/**
@struct DList_t
Generic doubly linked-list
*/
typedef struct DList_T {
  int size; ///< Number of elements in list

  int (*match)(const void *a, const void *b);
  void (*destroy)(void *data);

  DList_Element_t *head; ///< Pointer to first element in list
  DList_Element_t *tail; ///< Pointer to last element in list

} DList_t;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
Function to initialize a doubly linked-list

@pre
Must be called before list can be used by any other operation

The _destroy_ argument provides a way to free dynamically allocated data when
*dlist_destroy* is called. For example, if the list contains data dynamically
allocated using _malloc_, _destroy_ should be set to _free_ to free the data as
the doubly linked-list is destroyed. For a linked-list containing data that 
should not be freed, _destroy_ should be set to NULL.

Complexity: O(1)

@param [out] *list     The doubly linked-list to init
@param [in] (*destroy) Function pointer to free data element memory
*/
void dlist_init(DList_t *list, void (*destroy)(void *data));

/**
Function to destroy a doubly linked-list

The *dlist_destroy* operation removes all elements from a doubly linked-list and
calls the function passed as _destroy_ to *dlist_init* once for each element as 
it is removed, provided _destroy_ was not set to NULL.

@note
No operation is permitted after *dlist_destroy()* is called unless *dlist_init()*
is called again. 

Complexity: O(n)

@param [in,out] *list  The linked-list to destroy
*/
void dlist_destroy(DList_t *list);

/**
Function to insert an element into a doubly linked-list

Inserts an element just after _element_ into the doubly linked-list. When 
inserting into an emply list, _element_ should point to NULL. The new element 
contains a pointer to _data_, so the memory referenced by _data_ should remain
valid as long as the element remains in the list.

Complexity: O(1)

@param [in,out] *list     The linked-list to insert element into
@param [in]     *element  Pointer to element to insert after
@param [in]     *data     The data to insert

@return 0 if inserting into list was successful, otherwise -1
*/
int dlist_insert_next(DList_t *list, DList_Element_t *element, const void *data);

/**
Function to insert an element into a doubly linked-list

Inserts an element just before _element_ into the doubly linked-list. When 
inserting into an empty list, _element_ should point to NULL. The new element 
contains a pointer to _data_, so the memory referenced by _data_ should remain
valid as long as the element remains in the list.

Complexity: O(1)

@param [in,out] *list     The linked-list to insert element into
@param [in]     *element  Pointer to element to insert before
@param [in]     *data     The data to insert

@return 0 if inserting into list was successful, otherwise -1
*/
int dlist_insert_prev(DList_t *list, DList_Element_t *element, const void *data);

/**
Function to remove an element from a doubly linked list

Removes the element specified as _element_ from the doubly linked-list. Upon 
return _data_ points to the data stored in the element that was removed.

Complexity: O(1)

@param [in,out] *list     The linked-list to destroy
@param [in]     *element  Pointer to element to remove
@param [out]    **data    Pointer to data removed

@return 0 if inserting into list was successful, otherwise -1
*/
int dlist_remove(DList_t *list, DList_Element_t *element, void **data);

/**
MACRO that evaluates to the number of elements in the doubly linked-list
*/
#define dlist_size(list) ((list)->size)

/**
MACRO that evaluates to the element at the head of a doubly linked-list
*/
#define dlist_head(list) ((list)->head)

/**
MACRO that evaluates to the element at the tail of a doubly linked-list
*/
#define dlist_tail(list) ((list)->tail)

/**
MACRO that determines whether element is the head of doubly linked-list
*/
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

/**
MACRO that determines whether element is the tail of doubly linked-list
*/
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

/**
MACRO that evaluates to the data stored in given element of a doubly linked-list
*/
#define dlist_data(element) ((element)->data)

/**
MACRO that evaluates to the next element given an element in a doubly linked-list
*/
#define dlist_next(element) ((element)->next)

/**
MACRO that evaluates to the prev element given an element in a doubly linked-list
*/
#define dlist_prev(element) ((element)->prev)

#ifdef __cplusplus
}
#endif
#endif // DLIST_h
