/** 
@file list.h
@brief 
Definitions of a generic circular linked-list ADT

@note
Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)

@author Justin Hadella (pitchnogle@gmail.com)
*/
#ifndef CLIST_h
#define CLIST_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

/**
@struct CList_Element_t
Generic cicular linked-list element
*/
typedef struct CList_Element_T {
  void *data;                   ///< Pointer to data
  struct CList_Element_T *next; ///< Pointer to next element in list

} CList_Element_t;

/**
@struct CList_t
Generic cicular linked-list
*/
typedef struct CList_T {
  int size; ///< Number of elements in list

  int (*match)(const void *a, const void *b);
  void (*destroy)(void *data);

  CList_Element_t *head; ///< Pointer to first element in list

} CList_t;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
Function to initialize a circular linked-list

@pre
Must be called before list can be used by any other operation

The _destroy_ argument provides a way to free dynamically allocated data when
*list_destroy* is called. For example, if the list contains data dynamically
allocated using _malloc_, _destroy_ should be set to _free_ to free the data as
the linked-list is destroyed. For a circular linked-list containing data that 
should not be freed, _destroy_ should be set to NULL.

Complexity: O(1)

@param [out] *list     The circular linked-list to init
@param [in] (*destroy) Function pointer to free data element memory
*/
void clist_init(CList_t *list, void (*destroy)(void *data));

/**
Function to destroy a circular linked-list

The *list_destroy* operation removes all elements from a circular linked-list
and calls the function passed as _destroy_ to *clist_init* once for each element
as it is removed, provided _destroy_ was not set to NULL.

@note
No operation is permitted after *clist_destroy()* is called unless *clist_init()*
is called again. 

Complexity: O(n)

@param [in,out] *list  The circular linked-list to destroy
*/
void clist_destroy(CList_t *list);

/**
Function to insert an element into a cicular linked-list

Inserts an element just after _element_ into the circular linked-list. If 
_element_ is NULL, the new element is inserted at the head of the list. The
new element contains a pointer to _data_, so the memory referenced by _data_
should remain valid as long as the element remains in the list.

Complexity: O(1)

@param [in,out] *list     The circular linked-list to insert element into
@param [in]     *element  Pointer to element to insert after
@param [in]     *data     The data to insert

@return 0 if inserting into list was successful, otherwise -1
*/
int clist_insert_next(CList_t *list, CList_Element_t *element, const void *data);

/**
Function to remove an element from a circular linked list

Removes the element just past _element_ from the circular linked-list. Upon 
return _data_ points to the data stored in the element that was removed.

Complexity: O(1)

@param [in,out] *list     The circular linked-list to remove lelement from
@param [in]     *element  Pointer to element to remove after
@param [out]    **data    The data removed

@return 0 if inserting into list was successful, otherwise -1
*/
int clist_remove_next(CList_t *list, CList_Element_t *element, void **data);

/**
MACRO that evaluates to the number of elements in the circular linked-list
*/
#define clist_size(list) ((list)->size)

/**
MACRO that evaluates to the element at the head of a circular linked-list
*/
#define clist_head(list) ((list)->head)

/**
MACRO that evaluates to the data stored in given element of a circular linked-list
*/
#define clist_data(element) ((element)->data)

/**
MACRO that evaluates to the next element given an element in a circular linked-list
*/
#define clist_next(element) ((element)->next)

#ifdef __cplusplus
}
#endif
#endif // CSLIST_h
