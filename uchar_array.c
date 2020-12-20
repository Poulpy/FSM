#include "uchar_array.h"

struct char_array new_uchar_array(size_t len) {
    struct char_array ca;

    ca.chars = (unsigned char *) malloc(sizeof(unsigned char) * len);
    ca.len = len;

    return ca;
}

/**
 * Returns an array containing all ascii char
 */
struct char_array new_ascii_array() {
    struct char_array ca;

    ca.chars = (unsigned char *) malloc(sizeof(unsigned char) * 256);
    ca.len = 256;

    for (size_t i = 0; i != 256; i++) {
        ca.chars[i] = i;
    }

    return ca;
}

void append_uchar_array(struct char_array *ca, unsigned char c) {
    ca->chars = realloc(ca->chars, sizeof(unsigned char) * (ca->len + 1));
    ca->chars[ca->len] = c;
    ca->len++;
}

void free_uchar_array(struct char_array *ca) {
    free(ca->chars);
}
