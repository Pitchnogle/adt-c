/**
@file hashtable_example.c
@brief 
Example usage of chained hash table ADT

@author Justin Hadella (pitchnogle@gmail.com)
*/
#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "list.h"

#define HASH_TABLE_SIZE 11

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------

static int match_char(const void *char1, const void *char2);
static int hash_char(const void *key);

static void print_hashtable(const HashTable_t *htable);

// =============================================================================
// Main Program
// =============================================================================

int main(int argc, char *argv[])
{
  HashTable_t htable;
  char *data;
  char c;
  int retval;
  int i;

  // Initialize the chained hash table
  if (hashtable_init(&htable, HASH_TABLE_SIZE, hash_char, match_char, free) != 0)  
    return 1;
  
  // Perform some chained hash table operations

  for (i = 0; i < HASH_TABLE_SIZE; i++) {
    if ((data = (char *)malloc(sizeof(char))) == NULL)
      return 1;

   *data = ((5 + (i * 6)) % 23) + 'A';

  printf("inserting %c\n", *data);
  if (hashtable_insert(&htable, data) != 0)
    return 1;

    print_hashtable(&htable);
  }

  for (i = 0; i < HASH_TABLE_SIZE; i++) {
    if ((data = (char *)malloc(sizeof(char))) == NULL)
      return 1;

    *data = ((3 + (i * 4)) % 23) + 'a';

    printf("inserting %c\n", *data);
    if (hashtable_insert(&htable, data) != 0)
      return 1;

    print_hashtable(&htable);
  }

  if ((data = (char *)malloc(sizeof(char))) == NULL)
   return 1;

  *data = 'd';

  if ((retval = hashtable_insert(&htable, data)) != 0)
    free(data);

  fprintf(stdout, "Trying to insert d again...Value=%d (1=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL)
    return 1;

  *data = 'G';

  if ((retval = hashtable_insert(&htable, data)) != 0)
    free(data);

  fprintf(stdout, "Trying to insert G again...Value=%d (1=OK)\n", retval);

  fprintf(stdout, "Removing d, G, and S\n");

  c = 'd';
  data = &c;

  if (hashtable_remove(&htable, (void **)&data) == 0)
    free(data);

  c = 'G';
  data = &c;

  if (hashtable_remove(&htable, (void **)&data) == 0)
    free(data);

  c = 'S';
  data = &c;

  if (hashtable_remove(&htable, (void **)&data) == 0)
    free(data);

  print_hashtable(&htable);

  if ((data = (char *)malloc(sizeof(char))) == NULL)
    return 1;
  
  *data = 'd';

  if ((retval = hashtable_insert(&htable, data)) != 0)
    free(data);

  fprintf(stdout, "Trying to insert d again...Value=%d (0=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL)
    return 1;

  *data = 'G';

  if ((retval = hashtable_insert(&htable, data)) != 0)
    free(data);

  fprintf(stdout, "Trying to insert G again...Value=%d (0=OK)\n", retval);

  print_hashtable(&htable);

  fprintf(stdout, "Inserting X and Y\n");

  if ((data = (char *)malloc(sizeof(char))) == NULL)
    return 1;
  
  *data = 'X';

  if (hashtable_insert(&htable, data) != 0)
    return 1;

  if ((data = (char *)malloc(sizeof(char))) == NULL)
    return 1;

  *data = 'Y';

  if (hashtable_insert(&htable, data) != 0)
    return 1;

  print_hashtable(&htable);

  c = 'X';
  data = &c;

  if (hashtable_lookup(&htable, (void **)&data) == 0)
    fprintf(stdout, "Found an occurrence of X\n");
  else
    fprintf(stdout, "Did not find an occurrence of X\n");

  c = 'Z';
  data = &c;

  if (hashtable_lookup(&htable, (void **)&data) == 0)
    fprintf(stdout, "Found an occurrence of Z\n");
  else
    fprintf(stdout, "Did not find an occurrence of Z\n");
  
  // Destroy the chained hash table
  fprintf(stdout, "Destroying the hash table\n");
  hashtable_destroy(&htable);

  return 0;
}

// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Local Functions
// ~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

static int match_char(const void *char1, const void *char2)
{
  // Compare two characters
  return (*(const char *)char1 == *(const char *)char2);
}


static int hash_char(const void *key)
{
  // A simplistic hash function
  return *(const char *)key % HASH_TABLE_SIZE;
}


static void print_hashtable(const HashTable_t *htable)
{
  List_Element_t *element;
  int i;

  // Display the chained hash table
  fprintf(stdout, "Table size is %d\n", hashtable_size(htable));

  for (i = 0; i < HASH_TABLE_SIZE; i++) {
    fprintf(stdout, "Bucket[%03d]=", i);

    for (element = list_head(&htable->table[i]); element != NULL; element = list_next(element)) {
      fprintf(stdout, "%c", *(char *)list_data(element));
    }
    fprintf(stdout, "\n");
  }
}
