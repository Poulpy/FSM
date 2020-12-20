#ifndef NFA_H
#define NFA_H

#include<stdbool.h>
#include "int_array.h"

#define INITIAL_STATE 0

// nondeterministic finite automaton
struct nfa {
  unsigned int states_count;
  struct char_array alphabet;
  // array of binary values, of length states_count
  // if FINAL then state is final
  // else state is not final
  bool *final_states;
  struct transition *transitions;
};

struct transition {
  unsigned int initial_state;
  unsigned char symbol;
  // There can be multiple destination states for one state
  unsigned int *dest_states;
};

struct afn new_afn();
void free_afn(struct afn *a);
struct transition init_transition(unsigned int initial_state, unsigned char c, unsigned int final_state);

#endif
