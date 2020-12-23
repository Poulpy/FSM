#include "int_array.h"

/**
 * Initialize an array of unsigned int
 *
 * Note: don't forget to free
 */
struct int_array *new_int_array(size_t len) {
    struct int_array *ia;

    ia = (struct int_array *) calloc(sizeof(struct int_array), 1);
    ia->ints = (int *) calloc(sizeof(int), len);
    ia->len = len;

    return ia;
}


/**
 * Free an array of unsigned int
 */
void free_uint_array(struct int_array *ia) {
    free(ia->ints);
    free(ia);
}


/**
 * Returns the max value of the array
 */
unsigned int max_uint_array(struct int_array *ia) {
    unsigned int max;

    max = ia->ints[0];

    if (ia->len == 1) {
        return max;
    }

    for (size_t i = 1; i != ia->len; i++) {
        if (ia->ints[i] > max) {
            max = ia->ints[i];
        }
    }

    return max;
}


/**
 * Checks if 2 arrays are equal
 *
 * Note: Both arrays must be of same length
 */
bool eql_uint_array(struct int_array *ia1, struct int_array *ia2) {
    if (ia1->len != ia2->len) return false;

    for (size_t i = 0; i != ia1->len; i++) {
        if (ia1->ints[i] != ia2->ints[i]) {
            return false;
        }
    }

    return true;
}

/**
 * Copy the values of an array into another
 *
 * Note: both arrays must be of same length
 */
void copy_uint_array(struct int_array *to, struct int_array *from) {
    if (to->len != from->len) return;

    for (size_t i = 0; i != from->len; i++) {
        to->ints[i] = from->ints[i];
    }
}

void print_uint_array(struct int_array *ia) {
    for (size_t i = 0; i != ia->len; i++) {
        printf("%d ", ia->ints[i]);
    }
    puts("");
}

void print_uints_array(struct uints_array *uia) {
    for (size_t i = 0; i != uia->len; i++) {
        print_uint_array(uia->rows[i]);
    }
}




/*
 * Returns a 2D array of unsigned ints
 *
 * Note: Don't forget to free
 */
struct uints_array *new_uints_array(size_t row, size_t col) {
    struct uints_array *uia;
    struct int_array **ia;

    uia = (struct uints_array *) malloc(sizeof(struct uints_array));
    uia->rows = (struct int_array **) malloc(sizeof(struct int_array *) * row);

    for (size_t i = 0; i != row; i++) {
        uia->rows[i] = new_int_array(col);
    }

    uia->len = row;

    return uia;
}


/*
 * Free the memory of a 2D array of unsigned ints
 */
void free_uints_array(struct uints_array *uia) {
    for (size_t i = 0; i != uia->len; i++) {
        free_uint_array(uia->rows[i]);
    }

    free(uia->rows);

    free(uia);
}
