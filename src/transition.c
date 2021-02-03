#include "transition.h"

/**
 * Checks if 2 transitions are the same
 * TODO use memcmp, overkill but awesome af
 */
bool eql_transition(struct transition f1, struct transition f2) {
    return (f1.start_state == f2.start_state
            && f1.symbol == f2.symbol && f1.dest_state == f2.dest_state);
}

struct transition new_transition(unsigned int start_state, unsigned char c, unsigned int dest_state) {
    return (struct transition) { start_state, c, dest_state };
}

// not good
struct transition null_transition() {
    return (struct transition) { 0, 0, 0 };
}

void print_transition(struct transition t) {
    printf("%d %c %d\n", t.start_state, t.symbol, t.dest_state);
}
