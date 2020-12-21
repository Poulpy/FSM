#ifndef DFA_H
#define DFA_H

#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

// deterministic finite automaton
struct dfa {
  unsigned int states_count;
  unsigned char *alphabet;
  bool *final_states;// of length states_count
  struct function_array *func;// transition function
};

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


struct dfa *new_dfa(unsigned int states_count);
void append_transition(struct function_array *fa, struct ftransition t);
bool accept(struct dfa *d, unsigned char *word);

struct ftransition find_transition_with_start_state_and_symbol(struct dfa *d,
                                                               unsigned int start_state,
                                                               unsigned char symbol);
bool eql_ftransition(struct ftransition f1, struct ftransition f2);
struct ftransition null_transition();
struct function_array *new_function_array(size_t len);
void free_dfa(struct dfa *d);
void free_function_array(struct function_array *fa);
struct dfa *dfa_minimization(struct dfa *d);

struct dfa *dfa_minimization(struct dfa *d);


// utils
unsigned char *get_ascii_table();

#endif
