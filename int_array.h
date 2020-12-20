#ifndef UINT_ARRAY_H
#define UINT_ARRAY_H

#include<stdbool.h>
#include "stdlib.h"

struct int_array {
  unsigned int *ints;
  size_t len;
};

struct int_array new_int_array(size_t len);
void free_uint_array(struct int_array *ia);
unsigned int max_uint_array(struct int_array *ia);
// TODO
void append(struct int_array *ia, unsigned int i);
bool eql_uint_array(struct int_array *ia1, struct int_array *ia2);
bool contains_uint_array(struct int_array *container, struct int_array *ia);


#endif
