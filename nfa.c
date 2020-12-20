#include "nfa.h"

struct nfa new_nfa() {
    return (struct nfa) { 0, NULL, NULL };
}


struct nfa create_empty_language() {
    return (struct nfa) { 1, NULL, NULL };
}

/**
 * Note: Don't forget to free
 */
struct nfa create_empty_string_language() {
    bool *final_states;

    final_states = (bool *) malloc(sizeof(bool));
    final_states[0] = true;

    return (struct nfa) { 1, final_states, NULL };
}

void free_nfa(struct nfa *a) {
    if (a->final_states != NULL) {
        free(a->final_states);
    }

    if (&(a->trans) != NULL) {
        free_transition_array(&(a->trans));
    }
}


struct nfa create_language_from_char(unsigned char c) {
    struct nfa a;
    bool *final_states;

    a.states_count = 2;

    final_states = (bool *) malloc(sizeof(bool) * 2);
    final_states[0] = false;
    final_states[1] = true;

    a.trans = new_transition_array(1);
    a.trans.transitions[0] = new_transition(INITIAL_STATE, c, 1);

    return a;
}


