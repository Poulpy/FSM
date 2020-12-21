#ifndef TRANSITION_ARRAY_H
#define TRANSITION_ARRAY_H

#include<stdlib.h>
#include "int_array.h"

struct transition {
  unsigned int initial_state;
  unsigned char symbol;
  // There can be multiple destination states for one state
  struct int_array *dest_states;
};

struct transition_array {
    struct transition *transitions;
    size_t len;
};

struct transition_array new_transition_array(size_t len);
void free_transition_array(struct transition_array *ta);
void free_transition(struct transition *t);
void append_transition(struct transition_array *ta, struct transition t);
struct transition new_transition(unsigned int initial_state, unsigned char c,
                                 unsigned int dest_state);


#endif
