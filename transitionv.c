#include "transitionv.h"

struct transitionv *new_transitionv(size_t len) {
    struct transitionv *transition_vector;

    transition_vector = (struct transitionv *) malloc(sizeof(struct transitionv));

    transition_vector->v = (struct transition*) calloc(sizeof(struct transition), len);
    transition_vector->len = len;

    return transition_vector;
}

void free_transitionv(struct transitionv *transition_vector) {
    free(transition_vector->v);
    free(transition_vector);
}

void append_transitionv(struct transitionv *transition_vector, struct transition t) {
    transition_vector->v = realloc(transition_vector->v, sizeof(struct transition) * (transition_vector->len + 1));
    transition_vector->v[transition_vector->len] = t;
    transition_vector->len++;

}

void print_transitionv(struct transitionv *transition_vector) {
    printf("transitions : \n");
    for (size_t i = 0; i != transition_vector->len; i++) {
        print_transition(transition_vector->v[i]);
    }
}
