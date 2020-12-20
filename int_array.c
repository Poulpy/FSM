#include "int_array.h"

/**
 * Note: don't forget to free
 */
struct int_array new_int_array(size_t len) {
    struct int_array ia;

    ia.ints = (int *) malloc(sizeof(int) * len);
    ia.len = len;

    return ia;
}

void free_uint_array(struct int_array *ia) {
    free(ia->ints);
}


/**
 * Returns the max value of the array
 */
unsigned int max_uint_array(struct int_array *ia) {
    unsigned int max;

    for (size_t i = 0; i != ia->len; i++) {
        if (ia->ints[i] > max) {
            max = ia->ints[i];
        }
    }

    return max;
}


bool eql_uint_array(struct int_array *ia1, struct int_array *ia2) {
    if (ia1->len != ia2->len) {
        return false;
    } else {
        for (size_t i = 0; i != ia1->len; i++) {
            if (ia1->ints[i] != ia2->ints[i]) {
                return false;
            }
        }
    }

    return true;
}


