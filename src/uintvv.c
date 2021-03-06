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
 * Initialize a 2D array of unsigned ints and fill it with the variable number
 * of arguments
 *
 * Example: new_uintvv_and_fill(2, 2, 1, 0, 9, 3) gives [[1, 0], [9, 3]]
 *
 * Note: don't forget to free_uintvv
 */
struct uintvv *new_uintvv_and_fill(size_t vvlen, size_t vlen, ...) {
    struct uintvv *uint_matrix;
    struct uintv **uint_vector;
    va_list ap;

    uint_matrix = (struct uintvv *) malloc(sizeof(struct uintvv));
    uint_matrix->vv = (struct uintv **) malloc(sizeof(struct uintv *) * vvlen);
    uint_matrix->len = vvlen;

    for (size_t i = 0; i != vvlen; i++) {
        uint_matrix->vv[i] = new_uintv(vlen);
    }

    // filling the array with the values ...
    va_start(ap, vlen);
    for (size_t i = 0; i != vvlen; i++)  {
        for (size_t j = 0; j != vlen; j++) {
            uint_matrix->vv[i]->v[j] = va_arg(ap, unsigned int);
        }
    }
    va_end(ap);


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

/**
 * get_index_uintvv
 *
 * Returns the index where the value uint_vector
 * If the value is not found, it returns the length of uint_matrix
 * can't return -1 since the type is a size_t (unsigned int)
 */
size_t get_index_uintvv(struct uintvv *uint_matrix, struct uintv *uint_vector) {
    for (size_t i = 0; i != uint_matrix->len; i++) {
        if (eql_uintv(uint_matrix->vv[i], uint_vector)) {
            return i;
        }
    }

    return uint_matrix->len;
}

/**
 * Appends a new element to uint_matrix, at the end of the array
 */
void append_uintvv(struct uintvv *uint_matrix, struct uintv *uint_vector) {
    size_t len;

    len = uint_matrix->len;
    uint_matrix->vv = (struct uintv **) realloc(uint_matrix->vv, sizeof(struct uintv *) * (len + 1));
    uint_matrix->len++;
    uint_matrix->vv[len] = new_uintv(uint_vector->len);
    copy_uintv(uint_matrix->vv[len], uint_vector);
}

