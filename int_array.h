#ifndef UINT_ARRAY_H
#define UINT_ARRAY_H

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

// Array of unsigned integers
struct int_array {
    unsigned int *ints;
    size_t len;
};

// 2D array of unsigned integers
struct uints_array {
    struct int_array **rows;
    size_t len;
};

void print_uint_array(struct int_array *ia);
bool eql_uint_array(struct int_array *ia1, struct int_array *ia2);
struct int_array *new_int_array(size_t len);
unsigned int max_uint_array(struct int_array *ia);
void append(struct int_array *ia, unsigned int i);
void copy_uint_array(struct int_array *to, struct int_array *from);
void free_uint_array(struct int_array *ia);

struct uints_array *new_uints_array(size_t row, size_t col);
void free_uints_array(struct uints_array *uia, size_t row);

#endif
