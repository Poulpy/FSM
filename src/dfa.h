#ifndef DFA_H
#define DFA_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "uintv.h"
#include "uintvv.h"
#include "transitionv.h"

// deterministic finite automaton
struct dfa {
    unsigned int states_count;
    unsigned char *alphabet;
    bool *final_states;// of length states_count
    struct transitionv *func;// transition function
};

bool accept(struct dfa *d, unsigned char *word);
struct dfa *dfa_minimization(struct dfa *d);
struct dfa *new_dfa(unsigned int states_count, unsigned char *alphabet);
struct transition find_transition_with_start_state_and_symbol(struct dfa *d, unsigned int start_state, unsigned char symbol);
void free_dfa(struct dfa *d);
void print_dfa(struct dfa *d);

void deduce_states(struct uintvv *table, struct uintv *states);

unsigned char *get_ascii_table();
void set_all(bool *bool_array, size_t len, bool value);

#endif
