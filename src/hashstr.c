/** 
@file hashstr.c

See header

@author Justin Hadella (pitchnogle@gmail.com)
*/

#include "hashstr.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

unsigned int hashstr(const void *key)
{
  const char *str_ptr;
  unsigned int val;

  // Compute the hash

  val = 0;
  str_ptr = key;
  while (*str_ptr != '\0') {
    unsigned int tmp;

    val = (val << 4) + *str_ptr;

    if (tmp = (val & 0xf0000000)) {
      val = val ^ (tmp >> 24);
      val = val ^ tmp;
    }
    str_ptr++;
  }

  return val;
}
