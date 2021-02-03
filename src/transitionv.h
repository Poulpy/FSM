#ifndef TRANSITIONV_H
#define TRANSITIONV_H

#include <stdio.h>
#include <stdlib.h>

#include "transition.h"

// Vector of transitions
struct transitionv {
    struct transition *v;
    size_t len;
};

struct transitionv *new_transitionv(size_t len);
void append_transitionv(struct transitionv *transition_vector, struct transition t);
void free_transitionv(struct transitionv *transition_vector);
void print_transitionv(struct transitionv *transition_vector);

#endif
