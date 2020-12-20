#include "transition_array.h"

struct transition_array new_transition_array(size_t len) {
    struct transition_array ta;

    ta.transitions = (struct transition*) malloc(sizeof(struct transition) * len);
    ta.len = len;

    return ta;
}

void append_transition(struct transition_array *ta, struct transition t) {
    ta->transitions = realloc(ta->transitions, sizeof(struct transition) * (ta->len + 1));
    ta->transitions[ta->len] = t;
    ta->len++;
}

struct transition new_transition(unsigned int initial_state, unsigned char c,
                                 unsigned int dest_state) {

    return (struct transition) { initial_state, c, dest_state };
}

