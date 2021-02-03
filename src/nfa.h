#ifndef NFA_H
#define NFA_H

#include <stdbool.h>
#include <stdio.h>

#include "int_array.h"
#include "uchar_array.h"
#include "transition_array.h"

#define INITIAL_STATE 0

// nondeterministic finite automaton
struct nfa {
  unsigned int states_count;
  // array of binary values, of length states_count
  // if FINAL then state is final
  // else state is not final
  bool *final_states;
  struct transition_array *trans;

  // TODO is it really useful ?
  // struct char_array alphabet;
};


struct nfa new_nfa();
void free_nfa(struct nfa *a);

struct nfa create_empty_language();
struct nfa create_empty_string_language();
struct nfa create_language_from_char(unsigned char c);
struct nfa union_afn(struct nfa a1, struct nfa a2);
struct nfa concatenate_afn(struct nfa a1, struct nfa a2);
struct nfa kleene_closure(struct nfa a);

void print_nfa(struct nfa *a);

#endif
