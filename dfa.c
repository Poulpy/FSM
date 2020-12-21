#include "dfa.h"
#include<stdio.h>

bool accept(struct dfa *d, unsigned char *word) {
    unsigned int current_state;
    bool is_accepted;
    size_t i;
    struct ftransition transition;

    current_state = 0;
    i = 0;
    is_accepted = true;

    while (is_accepted == true && i != strlen(word)) {
        transition = find_transition_with_start_state_and_symbol(d, current_state, word[i]);

        if (eql_ftransition(null_transition(), transition)) {
            is_accepted = false;
        } else {
            current_state = transition.dest_state;
        }

        i++;
    }

    return is_accepted;
}

struct ftransition null_transition() {
    return (struct ftransition) { 0 , 0, 0 };
}

bool eql_ftransition(struct ftransition f1, struct ftransition f2) {
    if (f1.start_state == f2.start_state
        && f1.symbol == f2.symbol && f1.dest_state == f2.dest_state)

        return true;
    else
        return false;
}

struct ftransition find_transition_with_start_state_and_symbol(struct dfa *d,
                                                               unsigned int start_state,
                                                               unsigned char symbol) {
    size_t i;
    bool found;
    struct ftransition trans;

    i = 0;
    found = false;

    while (!found && i != d->func->len) {
        trans = d->func->transitions[i];

        if (trans.start_state == start_state && trans.symbol == symbol) {
            found = true;
        }

        i++;
    }

    if (found)
        return trans;
    else
        return null_transition();
}


struct function_array *new_function_array(size_t len) {
    struct function_array *fa;

    fa->transitions = (struct ftransition*) malloc(sizeof(struct ftransition) * len);
    fa->len = len;

    return fa;
}

void free_dfa(struct dfa *d) {
    free_function_array(d->func);
    free(d->final_states);
}

void free_function_array(struct function_array *fa) {
    free(fa->transitions);
}

void append_transition(struct function_array *fa, struct ftransition t) {
    fa->transitions = realloc(fa->transitions, sizeof(struct ftransition) * (fa->len + 1));
    fa->transitions[fa->len] = t;
    fa->len++;
}

