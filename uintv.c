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
 * Initialize a vector of unsigned int of length len and fill it with the values
 * given (variable number of arguments)
 *
 * Example: new_uintv_and_fill(3, 1, 0, 8) gives [1, 0, 8]
 * Note: don't forget to free
 */
struct uintv *new_uintv_and_fill(size_t len, ...) {
    struct uintv *uint_vector;
    va_list ap;

    uint_vector = (struct uintv *) calloc(sizeof(struct uintv), 1);
    uint_vector->v = (unsigned int *) calloc(sizeof(unsigned int), len);
    uint_vector->len = len;

    // filling the array with the values ...
    va_start(ap, len);
    for (size_t i = 0; i <= len; i++)  {
        uint_vector->v[i] = va_arg(ap, unsigned int);
    }
    va_end(ap);

    return uint_vector;
}

/**
 * Checks if 2 arrays are equal
 *
 * Note: Both arrays must be of same length
 */
bool eql_uintv(struct uintv *uint_vector1, struct uintv *uint_vector2) {
    if (uint_vector1->len != uint_vector2->len) return false;

    return (memcmp(uint_vector1->v, uint_vector2->v, sizeof(uint_vector1->len)) == 0);
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
 */
void copy_uintv(struct uintv *to, struct uintv *from) {
    if (to->len != from->len) return;

    memcpy(to->v, from->v, sizeof(from->v));
}

/**
 * concat_uintv
 *
 * Concatenate the vector to_add to the vector uint_vector
 * Example: concat_uintv([1, 2], [4, 2]) gives [1, 2, 4, 2]
 */
void concat_uintv(struct uintv *uint_vector, struct uintv *to_add) {
    size_t new_len, old_len;

    old_len = uint_vector->len;
    new_len = old_len + to_add->len;
    uint_vector->v = (unsigned int *) realloc(uint_vector->v, sizeof(unsigned int) * new_len);
    uint_vector->len = new_len;

    memcpy(&uint_vector->v[old_len], to_add->v, sizeof(to_add->v));
}

/**
 * append_uintv
 *
 * Append a new element at the end of the vector
 */
void append_uintv(struct uintv *uint_vector, unsigned int to_append) {
    size_t new_len;

    new_len = uint_vector->len + 1;
    uint_vector->v = (unsigned int *) realloc(uint_vector->v, sizeof(unsigned int) * new_len);
    uint_vector->len++;
    uint_vector->v[new_len - 1] = to_append;
}

