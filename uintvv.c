#include "uintvv.h"

/**
 * Initialize a 2D array of unsigned ints
 *
 * Note: don't forget to free_uintvv
 */
struct uintvv *new_uintvv(size_t vvlen, size_t vlen) {
    struct uintvv *uint_matrix;
    struct uintv **uint_vector;

    uint_matrix = (struct uintvv *) malloc(sizeof(struct uintvv));
    uint_matrix->vv = (struct uintv **) malloc(sizeof(struct uintv *) * vvlen);

    for (size_t i = 0; i != vvlen; i++) {
        uint_matrix->vv[i] = new_uintv(vlen);
    }

    uint_matrix->len = vvlen;

    return uint_matrix;
}

/**
 * Initialize a 2D array of unsigned ints
 *
 * Note: don't forget to free_uintvv
 */
void free_uintvv(struct uintvv *uint_matrix) {
    for (size_t i = 0; i != uint_matrix->len; i++) {
        free_uintv(uint_matrix->vv[i]);
    }

    free(uint_matrix->vv);

    free(uint_matrix);
}


/**
 * Prints a 2D array in the console
 */
void print_uintvv(struct uintvv *uint_matrix) {
    for (size_t i = 0; i != uint_matrix->len; i++) {
        print_uintv(uint_matrix->vv[i]);
    }
}
