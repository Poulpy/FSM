#ifndef DFA_H
#define DFA_H

#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "int_array.h"

// deterministic finite automaton
struct dfa {
    unsigned int states_count;
    unsigned char *alphabet;
    bool *final_states;// of length states_count
    struct function_array *func;// transition function
};

// array of transitions
struct function_array {
    struct ftransition *transitions;
    size_t len;
};

// transitions for dfa
struct ftransition {
    unsigned int start_state;
    unsigned char symbol;
    unsigned int dest_state;
};


bool accept(struct dfa *d, unsigned char *word);
struct dfa *dfa_minimization(struct dfa *d);
struct dfa *new_dfa(unsigned int states_count);
struct ftransition find_transition_with_start_state_and_symbol(struct dfa *d, unsigned int start_state, unsigned char symbol);
void free_dfa(struct dfa *d);
void print_dfa(struct dfa *d);

bool eql_ftransition(struct ftransition f1, struct ftransition f2);
struct ftransition null_transition();
struct function_array *new_function_array(size_t len);
void append_transition(struct function_array *fa, struct ftransition t);
void print_transitions(struct function_array *fa);
void free_function_array(struct function_array *fa);

void deduce_states(struct uints_array *table, struct int_array *states);

unsigned char *get_ascii_table();
void set_all(bool *bool_array, size_t len, bool value);

#endif
