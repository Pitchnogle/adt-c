/** 
@file hashstr.h
@brief 
Definitions of a hash function for strings

@note
Code based on content from "Mastering Algorithms with C" (O'Reilly 1999)

@author Justin Hadella (pitchnogle@gmail.com)
*/
#ifndef HASHSTR_h
#define HASHSTR_h

#ifdef __cplusplus
extern "C"
{
#endif

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Public Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
Hash function for use with strings

@param [in] *key  The key to compute a hash for (a string)
@return the hash for given string
*/
unsigned int hashstr(const void *key);

#ifdef __cplusplus
}
#endif
#endif // HASHSTR_h
