#include "dfa.h"

struct dfa *new_dfa(unsigned int states_count) {
    struct dfa *d;

    d = (struct dfa *) malloc(sizeof(struct dfa));
    d->states_count = states_count;

    d->final_states = (bool *) malloc(sizeof(bool) * states_count);
    for (size_t i = 0; i != states_count; i++) {
        d->final_states[i] = false;
    }

    return d;
}

/**
 * Note: don't forget to free
 */
struct ftransition new_ftransition(unsigned int start_state, unsigned char c,
                                   unsigned int dest_state) {

    return (struct ftransition) { start_state, c, dest_state };
}

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

    fa = (struct function_array *) malloc(sizeof(struct function_array));

    fa->transitions = (struct ftransition*) malloc(sizeof(struct ftransition) * len);
    fa->len = len;

    return fa;
}

void free_dfa(struct dfa *d) {
    free(d->func->transitions);
    free(d->func);
    free(d->final_states);
    free(d->alphabet);
    free(d);
}

void free_function_array(struct function_array *fa) {
    free(fa->transitions);
}

void append_transition(struct function_array *fa, struct ftransition t) {
    fa->transitions = realloc(fa->transitions, sizeof(struct ftransition) * (fa->len + 1));
    fa->transitions[fa->len] = t;
    fa->len++;
}


struct dfa *dfa_minimization(struct dfa *d) {
    struct uints_array *table;
    struct ftransition trans;
    struct int_array *states, *states_before;
    bool *done, *new_final_states;
    unsigned int new_states_count, states_count;
    struct dfa *dfa_minimized;
    struct function_array *new_function;


    states = new_int_array(d->states_count);
    states_before = new_int_array(d->states_count);
    states_count = d->states_count;
    table = new_uints_array(strlen(d->alphabet), states_count);

    // initialization
    for (size_t i = 0; i != states_count; i++) {
        if (d->final_states[i] == true) {
            states->ints[i] = 1;
        } else {
            states->ints[i] = 0;
        }
    }

    // write transitions in table
    for (size_t i = 0; i != 2; i++) {
        for (size_t start_state = 0; start_state != states_count; start_state++) {
            for (size_t s = 0; s != strlen(d->alphabet); s++) {
                trans = find_transition_with_start_state_and_symbol(d, start_state, d->alphabet[s]);
                // Stock the value (see initialisation) of the destination state
                table->rows[s]->ints[start_state] = states->ints[trans.dest_state];
            }
        }
        // check which states has the same transitions
        deduce_states(table, states);
        copy_uint_array(states_before, states);
    }

    // We loop till we reach the same conclusion twice
    while (eql_uint_array(states_before, states) == false) {
        for (size_t start_state = 0; start_state != states_count; start_state++) {
            for (size_t s = 0; s != strlen(d->alphabet); s++) {
                trans = find_transition_with_start_state_and_symbol(d, start_state, d->alphabet[s]);
                table->rows[s]->ints[start_state] = states->ints[trans.dest_state];
            }
        }
        deduce_states(table, states);
        copy_uint_array(states_before, states);
    }

    new_states_count = max_uint_array(states);
    done = (bool *) malloc(sizeof(bool) * new_states_count);
    new_final_states = (bool *) malloc(sizeof(bool) * new_states_count);

    // set all values to false
    for (size_t i = 0; i != new_states_count; i++) {
        done[i] = false;
    }
    new_function = new_function_array(new_states_count * strlen(d->alphabet));

    // We create the transitions
    // i : symbol
    // j : start state
    for (size_t j = 0; j != table->len; j++) {
        for (size_t i = 0; i != strlen(d->alphabet); i++) {
            trans = new_ftransition(states->ints[j], d->alphabet[i], table->rows[j]->ints[i]);

            // Since some columns may be redundant, we check in a boolean
            // array if we already checked them
            if (*(done+states->ints[j]) == false) {
                new_function->transitions[i + j] = trans;
            }
        }
        *(done+states->ints[j]) = true;
    }

    // set all values to false
    for (size_t i = 0; i != new_states_count; i++) {
        done[i] = false;
    }

    // deduce final states
    for (size_t i = 0; i != states_count; i++) {
        if (*(done+states->ints[i]) == false && d->final_states[i] == true) {
            new_final_states[states->ints[i]] = true;
            *(done+states->ints[i]) = true;
        }
    }

    //dfa = new_dfa(len(states), alphabet, final_states, transitions);
    dfa_minimized = new_dfa(new_states_count);
    //dfa_minimized->alphabet = (unsigned char *) strdup((const char *) d->alphabet);
    memcpy(dfa_minimized->alphabet, d->alphabet, sizeof(d->alphabet));
    dfa_minimized->final_states = new_final_states;
    dfa_minimized->func = new_function;

    free_uint_array(states);
    free_uint_array(states_before);
    free(done);

    return dfa_minimized;
}

// TODO
void deduce_states(struct uints_array *table, struct int_array *states) {
    for (size_t i = 0; i != states->len; i++) {
        states->ints[i] = i;

        for (size_t j = i + 1; j != states->len; j++) {
            if (eql_uint_array(table->rows[i], table->rows[j]) == true) {
                states->ints[j] = i;
            }
        }
    }
}


// utils
unsigned char *get_ascii_table() {
    unsigned char *ascii_table;

    ascii_table = (unsigned char *) calloc(257, sizeof(unsigned char));
    for (size_t i = 0; i != 256; i++) {
        ascii_table[i] = i;
    }

    return ascii_table;
}