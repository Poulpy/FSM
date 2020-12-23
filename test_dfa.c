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

void test_deduce_states() {
    struct int_array *states;
    struct uints_array *uia;
    size_t rows;

    rows = 3;
    states = new_int_array(rows);
    uia = new_uints_array(rows, rows);

    for (size_t i = 0; i != 3; i++) {
        uia->rows[0]->ints[i] = 1;
        uia->rows[1]->ints[i] = 2;
        uia->rows[2]->ints[i] = 2;
    }

    deduce_states(uia, states);
    if (states->ints[0] == 0 && states->ints[1] == 1 && states->ints[2] == 1) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_uints_array(uia);
    free_uint_array(states);
}

void test_dfa_minimization() {
    struct dfa *d, *minimized_dfa;

    d = new_dfa(8);
    d->final_states[4] = true;
    d->final_states[5] = true;
    d->final_states[6] = true;
    d->final_states[7] = true;
    d->alphabet = (unsigned char *) malloc(sizeof(unsigned char) * 3);
    d->alphabet[0] = 'a';
    d->alphabet[1] = 'b';
    d->alphabet[2] = '\0';
    d->func = new_function_array(16);

    d->func->transitions[0] = (struct ftransition) { 0, 'a', 1 };
    d->func->transitions[1] = (struct ftransition) { 0, 'b', 0 };
    d->func->transitions[2] = (struct ftransition) { 1, 'a', 2 };
    d->func->transitions[3] = (struct ftransition) { 1, 'b', 3 };
    d->func->transitions[4] = (struct ftransition) { 2, 'a', 5 };
    d->func->transitions[5] = (struct ftransition) { 2, 'b', 3 };
    d->func->transitions[6] = (struct ftransition) { 3, 'a', 4 };
    d->func->transitions[7] = (struct ftransition) { 3, 'b', 0 };
    d->func->transitions[8] = (struct ftransition) { 4, 'a', 5 };
    d->func->transitions[9] = (struct ftransition) { 4, 'b', 6 };
    d->func->transitions[10] = (struct ftransition) { 5, 'a', 5 };
    d->func->transitions[11] = (struct ftransition) { 5, 'b', 6 };
    d->func->transitions[12] = (struct ftransition) { 6, 'a', 4 };
    d->func->transitions[13] = (struct ftransition) { 6, 'b', 7 };
    d->func->transitions[14] = (struct ftransition) { 7, 'a', 4 };
    d->func->transitions[15] = (struct ftransition) { 7, 'b', 7 };
    print_dfa(d);
    minimized_dfa = dfa_minimization(d);
    print_dfa(minimized_dfa);
    free_dfa(d);
    free(minimized_dfa);
}

int main() {
    test_accept();
    //test_deduce_states(); memleaks
    test_dfa_minimization();

    return 0;
}
