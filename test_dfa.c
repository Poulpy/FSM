#include<stdio.h>
#include<stdbool.h>
#include "dfa.h"
#include "uintv.h"

void test_accept() {
    struct dfa *d;
    struct ftransition t;
    unsigned char *alphabet;

    t.start_state = 0;
    t.symbol = 'b';
    t.dest_state = 1;

    alphabet = get_ascii_table();
    d = new_dfa(2, alphabet);
    d->final_states[1] = true;
    d->func = new_function_array(0);

    append_transition(d->func, t);
    //printf("len %d\n", d->func->len);
    if (accept(d, "b")) {
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

    struct dfa *d2;

    d2 = new_dfa(2, alphabet);
    //d2->alphabet = get_ascii_table();
    d2->func = new_function_array(0);
    append_transition(d2->func, new_ftransition(0, 'c', 1));
    if (!accept(d, "c")) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_dfa(d);
    free_dfa(d2);
    free(alphabet);
}

void test_deduce_states() {
    struct uintv *states;
    struct uintvv *uia;
    size_t rows;

    rows = 3;
    states = new_uintv(rows);
    uia = new_uintvv(rows, rows);

    for (size_t i = 0; i != 3; i++) {
        uia->vv[0]->v[i] = 1;
        uia->vv[1]->v[i] = 2;
        uia->vv[2]->v[i] = 2;
    }

    deduce_states(uia, states);
    if (states->v[0] == 0 && states->v[1] == 1 && states->v[2] == 1) {
        printf("OK\n");
    } else {
        printf("KO\n");
    }

    free_uintvv(uia);
    free_uintv(states);
}

void test_dfa_minimization() {
    struct dfa *d, *minimized_dfa;
    unsigned char *alphabet;

    alphabet = (unsigned char *) malloc(sizeof(unsigned char) * 3);
    strcpy(alphabet, "ab");
    d = new_dfa(8, alphabet);
    d->final_states[4] = true;
    d->final_states[5] = true;
    d->final_states[6] = true;
    d->final_states[7] = true;
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
    test_deduce_states();
    test_dfa_minimization();

    return 0;
}
