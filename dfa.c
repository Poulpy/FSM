#include "dfa.h"
#include<stdio.h>
#include<string.h>

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

/*
struct dfa *dfa_minimization(struct dfa *d) {
    t1 = [[]];
    t2 = [[]];
    done = [0] * afd.states;

    struct int_array *states;
    struct int_array *states_before;

    states = new_int_array(d->states_count);
    states_before = new_int_array(d->states_count);

    final_states = afd.final_states;

    for (size_t i = 0; i != d->states_count; i++) {
        if (d->final_states[i] == true) {
            states[i] = 1;
        } else {
            states[i] = 0;
        }
    }


    for (size_t i = 0; i != 2; i++) {

    }
    faire 2 fois
      pour un sommet s donné, i
        pour un symbole c donné, j
          dst = prendre la transition partant de s avec la lettre a
          prendre le numéro de dst
          t1[i][j] = dst
      deduce_states(states, t1)
      states_before = states


    tant que states_before != states
      pour un sommet s donné
        pour un symbole c donné
          dst = prendre la transition partant de s avec la lettre a
          prendre le numéro de dst
      deduce_states(states, t1)
      states_before = states


    for (size_t i = 0; i != len(t1); i++) {
      for (size_t j = 0; j != len(t1[i]); j++) {
        t = new_transition(states[j], alphabet[i], t1[i][j]);

        if (!done[states[j]]) {
          transitions << t;
        }
      }
      done[states[j]] = 1;
    }

    real_states = max(states);
    // mettre done à 0 partout

    // deduce final states
    for (size_t i = 0; i != len(tates); i++) {
      if (!done[states[i]] && final_states.contains(i)) {
        new_final_states << states[i];
        done[states[i]] = 1;
      }
    }

    dfa = new_dfa(len(states), alphabet, final_states, transitions);

    free(states);
    free(states_before);
}
*/

// utils
unsigned char *get_ascii_table() {
    unsigned char *ascii_table;

    ascii_table = (unsigned char *) calloc(257, sizeof(unsigned char));
    for (size_t i = 0; i != 256; i++) {
        ascii_table[i] = i;
    }

    return ascii_table;
}
