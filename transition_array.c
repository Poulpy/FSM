#include "transition_array.h"

struct transition_array new_transition_array(size_t len) {
    struct transition_array ta;

    ta.transitions = (struct transition*) malloc(sizeof(struct transition) * len);
    ta.len = len;

    return ta;
}

// TODO append transition to already existing transition
void append_transition(struct transition_array *ta, struct transition t) {
    ta->transitions = realloc(ta->transitions, sizeof(struct transition) * (ta->len + 1));
    ta->transitions[ta->len] = t;
    ta->len++;
}

/**
 * Note: don't forget to free
 */
struct transition new_transition(unsigned int initial_state, unsigned char c,
                                 unsigned int dest_state) {

    struct int_array dest_states;

    dest_states = new_int_array(1);
    dest_states.ints[0] = dest_state;

    return (struct transition) { initial_state, c, &dest_states };
}

void free_transition(struct transition *t) {
    free_uint_array(t->dest_states);
}

void free_transition_array(struct transition_array *ta) {
    for (size_t i = 0; i != ta->len; i++) {
        free_transition(&(ta->transitions[i]));
    }

    free(ta->transitions);
}
