#ifndef TRANSITION_H
#define TRANSITION_H

#include <stdbool.h>
#include <stdio.h>

// (Transition struct only for DFA)
struct transition {
    unsigned int start_state;
    unsigned char symbol;
    unsigned int dest_state;
};

bool eql_transition(struct transition f1, struct transition f2);
struct transition new_transition(unsigned int start_state, unsigned char c, unsigned int dest_state);
struct transition null_transition();
void print_transition(struct transition t);

#endif
