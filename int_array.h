#ifndef UINT_ARRAY_H
#define UINT_ARRAY_H

#include "stdlib.h"

struct int_array {
  unsigned int *ints;
  size_t len;
};

struct int_array init_uint_array(size_t len);
void free_uint_array(struct int_array *ia);
unsigned int max_uint_array(struct int_array *ia);
// TODO
void append(struct int_array *ia, unsigned int i);

#endif
