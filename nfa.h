#ifndef NFA_H
#define NFA_H

#include<stdbool.h>
#include "int_array.h"

#define INITIAL_STATE 0
#define FINAL 0
#define NOT_FINAL 1

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


// alphabet
struct char_array {
  unsigned char *chars;
  size_t len;
};

struct int_array new_int_array(int len);
int eql_int_array(struct int_array *ia1, struct int_array *ia2);
int contains(struct int_array *container, struct int_array ia);

int append(struct char_array *ca, char c);

struct afn init_afn();
void free_afn(struct afn *a);
struct transition init_transition(unsigned int initial_state, unsigned char c, unsigned int final_state);

#endif
