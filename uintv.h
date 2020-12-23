#ifndef UINTV_H
#define UINTV_H

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

// Vector of unsigned int
struct uintv {
    unsigned int *v;
    size_t len;
};

// Vector of vectors unsigned int
struct uintvv {
    struct uintv **v;
    size_t len;
};

bool eql_uintv(struct uintv *uint_vector1, struct uintv *uint_vector2);
struct uintv *new_uintv(size_t len);
void copy_uintv(struct uintv *to, struct uintv *from);
void free_uintv(struct uintv *uint_vector);
void print_uintv(struct uintv *uint_vector);

struct uintvv *new_uintvv(size_t vvlen, size_t vlen);
void free_uintvv(struct uintvv *uint_matrix);
void print_uintvv(struct uintvv *uint_matrix);

#endif
