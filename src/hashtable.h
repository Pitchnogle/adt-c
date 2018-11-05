/** 
@file hashtable.h
@brief 
Definitions of a generic chained hash table

@note
Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)

@author Justin Hadella (pitchnogle@gmail.com)
*/
#ifndef HASHTABLE_h
#define HASHTABLE_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#include "list.h"

// -----------------------------------------------------------------------------
// Definitions
// -----------------------------------------------------------------------------

typedef struct HashTable_T {
  int buckets; ///< The number of buckets in the hash table

  int (*hash)(const void *key);
  int (*match)(const void *a, const void *b);
  void (*destroy)(void *data);

  int size;       ///< The number of elements in the hash table
  List_t *table;  ///< The hash table itself is a pointer to array of lists

} HashTable_t;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
Function to initialize a chained hash table

@pre
Must be called before hash table can be used by any other operation

The number of buckets allocated in the hash table is specified by _buckets_. The
function pointer _hash_ specifies a user-defined hash function. The function
pointer _match_ specifies a user-defined to determine whether two keys match.
The _destroy_ argument provides a way to free dynamically allocated data when
*hashtable_destroy* is called. 

Complexity: O(m), where *m* is the number of buckets in the hash table

@param [out] *htable  The hash table to init
@param [in]   buckets The number of buckets in the hash table
@param [in]  *hash    Pointer to user hash function
@param [in]  *match   Pointer to user hash key comparison function
@param [in]  *destroy Pointer to function to free element memory

@returns 0 if hash table initialization successful, otherwise -1
*/
int hashtable_init(HashTable_t *htable, int buckets, 
                   int (*hash)(const void *key),
                   int (*match)(const void *a, const void *b),
                   void (*destroy)(void *data));

/**
Function to destroy a chained hash table

The *hashtable_destroy* operation removes all elements from chained hash table
and calls the function passed as _destroy_ to *hashtable_init* once for each 
element as it is removed, provided _destroy_ was not set to NULL.

Complexity: O(m), where *m* is the number of buckets in the hash table

@param [in,out] *htable  The chained hash table to destroy
*/
void hashtable_destroy(HashTable_t *htable);

/**
Function to insert an element into a chained hash table

Complexity: O(1)

@param [in,out] *htable  The chained hash table to insert into
@param [in]     *data    The data to insert

@returns 0 if inserting the element was successful, 1 if the element was already
in the hash table, otherwise -1
*/
int hashtable_insert(HashTable_t *htable, const void *data);

/**
Function to remove an element from a chained hash table

Complexity: O(1)

@param [in,out] *htable  The chained hash table remove data from
@param [out]    **data   The data removed

@returns 0 if removing the element was successful, otherwise -1
*/
int hashtable_remove(HashTable_t *htable, void **data);

/**
Function to determine if an element is contained within the chained hash table

Complexity: O(1)

@param [in,out] *htable  The chained hash table to lookup
@param [out]    **data   Pointer to matching data (NULL if not found)

@returns 0 if the element was found in the chained hash table, otherwise -1
*/
int hashtable_lookup(HashTable_t *htable, void **data);

/**
MACRO that evaluates to the number of elements in the hash table
*/
#define hashtable_size(htable) ((htable)->size)

#ifdef __cplusplus
}
#endif
#endif // HASHTABLE_h
