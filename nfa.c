#include "nfa.h"

struct nfa new_nfa() {
    return (struct nfa) { 0, (char_array) NULL, NULL, NULL };
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
    if (a->trans != NULL) {
        free(a->trans);
    }
}
