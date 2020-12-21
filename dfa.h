#ifndef DFA_H
#define DFA_H

#include<stdbool.h>

// deterministic finite automaton
struct dfa {
  unsigned int states_count;
  struct char_array *alphabet;
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


struct dfa *new_dfa(unsigned int states_count, bool *final_states);
void append_transition(struct dfa *d, struct ftransition ft);
bool accept(struct dfa *d, struct char_array *word);

struct ftransition find_transition_with_start_state_and_symbol(struct dfa *d,
                                                               unsigned int start_state,
                                                               unsigned char symbol);
bool eql_ftransition(struct ftransition f1, struct ftransition f2);
struct ftransition null_transition();
struct function_array *new_function_array(size_t len);
void free_dfa(struct dfa *d);
void free_function_array(struct function_array *fa);

#endif
