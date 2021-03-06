#ifndef UINTV_H
#define UINTV_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// Vector of unsigned int
struct uintv {
    unsigned int *v;
    size_t len;
};

bool eql_uintv(struct uintv *uint_vector1, struct uintv *uint_vector2);
struct uintv *new_uintv(size_t len);
void concat_uintv(struct uintv *uint_vector, struct uintv *to_add);
void copy_uintv(struct uintv *to, struct uintv *from);
void free_uintv(struct uintv *uint_vector);
void print_uintv(struct uintv *uint_vector);
void append_uintv(struct uintv *uint_vector, unsigned int to_append);
void clear_uintv(struct uintv *uint_vector);
struct uintv *new_uintv_and_fill(size_t len, ...);

#endif
