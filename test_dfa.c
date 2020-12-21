#include<stdio.h>
#include<stdbool.h>
#include "dfa.h"

void test_accept() {
    struct dfa d;
    struct ftransition t;

    t.start_state = 0;
    t.symbol = 'b';
    t.dest_state = 1;

    d.states_count = 2;
    d.func = new_function_array(1);

    append_transition(d.func, t);
    if (accept(&d, "b") == true) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }
    if (accept(&d, "c") == false) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_dfa(&d);
}

int main() {
    test_accept();
    return 0;
}
