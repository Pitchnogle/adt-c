/** 
@file hashtable.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int hashtable_init(HashTable_t *htable, int buckets, 
                   int (*hash)(const void *key),
                   int (*match)(const void *a, const void *b),
                   void (*destroy)(void *data))
{
  int i;

  // Allocate space for the hash table
  if ((htable->table = (List_t*)malloc(buckets * sizeof (List_t))) == NULL)
    return -1;
  
  // Initialize the buckets
  htable->buckets = buckets;
  for (i = 0; i < htable->buckets; i++)
    list_init(&htable->table[i], destroy);
  
  htable->hash = hash;
  htable->match = match;
  htable->destroy = destroy;
  htable->size = 0;

  return 0;
}


void hashtable_destroy(HashTable_t *htable)
{
  // Destroy each bucket
  int i;
  for (i = 0; i < htable->buckets; i++)
    list_destroy(&htable->table[i]);

  // Free memory allocated for the hash table
  free(htable->table);

  // No operations permitted at this point -- clear memory as precaution
  memset(htable, 0, sizeof (HashTable_t));
}


int hashtable_insert(HashTable_t *htable, const void *data)
{
  void *tmp;
  int bucket;
  int retval;

  // Do nothing if the data is already in the table
  tmp = (void*)data;
  if (hashtable_lookup(htable, &tmp) == 0)
    return 1;

  // Calculate the hash
  bucket = htable->hash(data) % htable->buckets;

  // Insert the data into the bucket
  if ((retval = list_insert_next(&htable->table[bucket], NULL, data)) == 0)
    htable->size++;
  
  return retval;
}


int hashtable_remove(HashTable_t *htable, void **data)
{
  List_Element_t *element;
  List_Element_t *prev;
  int bucket;

  // Calculate the hash
  bucket = htable->hash(*data) % htable->buckets;

  // Search for the data in the bucket
  prev = NULL;
  for (element = list_head(&htable->table[bucket]); element != NULL; element = list_next(element)) {
    if (htable->match(*data, list_data(element))) {
      // Remove the data from the bucket
      if (list_remove_next(&htable->table[bucket], prev, data) == 0) {
        htable->size--;
        return 0;
      }
      else {
        return -1;
      }
    }
    prev = element;
  }

  // Return that the data was not found
  return -1;
}


int hashtable_lookup(HashTable_t *htable, void **data)
{
  List_Element_t *element;
  int bucket;

  // Calculate the hash
  bucket = htable->hash(*data) % htable->buckets;

  // Search for the data in the bucket
  for (element = list_head(&htable->table[bucket]); element != NULL; element = list_next(element)) {
    if (htable->match(*data, list_data(element))) {
      // Pass back the data from the table
      *data = list_data(element);
      return 0;
    }
  }

  // Return that the data was not found
  return -1;
}
