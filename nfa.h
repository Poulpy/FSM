#ifndef NFA_H
#define NFA_H

#include<stdbool.h>

#include "int_array.h"
#include "uchar_array.h"
#include "transition_array.h"

#define INITIAL_STATE 0

// nondeterministic finite automaton
struct nfa {
  unsigned int states_count;
  struct char_array alphabet;
  // array of binary values, of length states_count
  // if FINAL then state is final
  // else state is not final
  bool *final_states;
  struct transition_array trans;
};


struct afn new_afn();
void free_afn(struct afn *a);

#endif
