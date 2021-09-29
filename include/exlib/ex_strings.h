#ifndef EX_STRINGS_H_INCLUDED
#define EX_STRINGS_H_INCLUDED


#include <exlib/ex_types.h>


size_t ex_strlcpy(char* destination, const char* source, size_t dsize);
size_t ex_strlcat(char* destination, const char* source, size_t dsize);


#endif /* EX_STRINGS_H_INCLUDED */
