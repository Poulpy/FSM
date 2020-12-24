#ifndef UINTVV_H
#define UINTVV_H

#include "uintv.h"

// Vector of vectors unsigned int
struct uintvv {
    struct uintv **vv;
    size_t len;
};

struct uintvv *new_uintvv(size_t vvlen, size_t vlen);
void free_uintvv(struct uintvv *uint_matrix);
void print_uintvv(struct uintvv *uint_matrix);
// TODO
void append_uintvv(struct uintvv *uint_matrix, struct uintv *uint_vector);
size_t get_index_uintvv(struct uintvv *uint_matrix, struct uintv *uint_vector);

#endif
