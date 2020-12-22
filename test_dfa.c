#include<stdio.h>
#include<stdbool.h>
#include "dfa.h"

void test_accept() {
    struct dfa *d;
    struct ftransition t;

    t.start_state = 0;
    t.symbol = 'b';
    t.dest_state = 1;

    d = new_dfa(2);
    d->final_states[1] = true;
    d->alphabet = get_ascii_table();
    d->func = new_function_array(1);

    append_transition(d->func, t);
    if (accept(d, "b") == true) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }
    if (accept(d, "ba") == false) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }
    if (accept(d, "ab") == false) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }
    if (accept(d, "c") == false) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_dfa(d);
}

// leaks
void test_deduce_states() {
    struct int_array *states;
    struct uints_array *uia;
    size_t rows;

    rows = 3;
    states = new_int_array(rows);
    uia = new_uints_array(rows, 3);
    for (size_t i = 0; i != 3; i++) {
        uia->rows[0]->ints[i] = 1;
        uia->rows[1]->ints[i] = 2;
        uia->rows[2]->ints[i] = 2;
    }
    //uia->rows[1] = ia2;
    deduce_states(uia, states);
    if (states->ints[0] == 0 && states->ints[1] == 1
        && states->ints[2] == 1) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_uints_array(uia, rows);
    free_uint_array(states);
}

int main() {
    test_accept();
    test_deduce_states();

    return 0;
}
