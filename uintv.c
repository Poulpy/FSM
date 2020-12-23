#include "uintv.h"

/**
 * Initialize an array of unsigned int
 *
 * Note: don't forget to free
 */
struct uintv *new_uintv(size_t len) {
    struct uintv *uint_vector;

    uint_vector = (struct uintv *) calloc(sizeof(struct uintv), 1);
    uint_vector->v = (unsigned int *) calloc(sizeof(unsigned int), len);
    uint_vector->len = len;

    return uint_vector;
}

/**
 * Checks if 2 arrays are equal
 *
 * Note: Both arrays must be of same length
 * TODO: try memcmp ?
 */
bool eql_uintv(struct uintv *uint_vector1, struct uintv *uint_vector2) {
    if (uint_vector1->len != uint_vector2->len) return false;

    for (size_t i = 0; i != uint_vector1->len; i++) {
        if (uint_vector1->v[i] != uint_vector2->v[i]) {
            return false;
        }
    }

    return true;
}

/**
 * Free the struct uintv
 */
void free_uintv(struct uintv *uint_vector) {
    free(uint_vector->v);
    free(uint_vector);
}

/**
 * Prints in the console the values of the array
 */
void print_uintv(struct uintv *uint_vector) {
    for (size_t i = 0; i != uint_vector->len; i++) {
        printf("%d ", uint_vector->v[i]);
    }
    puts("");
}

/**
 * Copy the values of an array into another
 *
 * Note: both arrays must be of same length
 * TODO: try memcpy ?
 */
void copy_uintv(struct uintv *to, struct uintv *from) {
    if (to->len != from->len) return;

    for (size_t i = 0; i != from->len; i++) {
        to->v[i] = from->v[i];
    }
}




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

    for (size_t i = 0; i != row; i++) {
        uint_matrix->vv[i] = new_int_array(vlen);
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
        free_uint_array(uint_matrix->vv[i]);
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
