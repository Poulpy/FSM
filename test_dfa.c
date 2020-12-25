#include<stdio.h>
#include<stdbool.h>
#include "dfa.h"
#include "uintv.h"

void test_accept() {
    struct dfa *d;
    unsigned char *alphabet;

    alphabet = get_ascii_table();
    d = new_dfa(2, alphabet);
    d->final_states[1] = true;
    d->func = new_transitionv(0);

    append_transitionv(d->func, new_transition(0, 'b', 1));
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
    d2->func = new_transitionv(0);
    append_transitionv(d2->func, new_transition(0, 'c', 1));
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
    d->func = new_transitionv(16);

    d->func->v[0] = new_transition(0, 'a', 1);
    d->func->v[1] = new_transition(0, 'b', 0);
    d->func->v[2] = new_transition(1, 'a', 2);
    d->func->v[3] = new_transition(1, 'b', 3);
    d->func->v[4] = new_transition(2, 'a', 5);
    d->func->v[5] = new_transition(2, 'b', 3);
    d->func->v[6] = new_transition(3, 'a', 4);
    d->func->v[7] = new_transition(3, 'b', 0);
    d->func->v[8] = new_transition(4, 'a', 5);
    d->func->v[9] = new_transition(4, 'b', 6);
    d->func->v[10] = new_transition(5, 'a', 5);
    d->func->v[11] = new_transition(5, 'b', 6);
    d->func->v[12] = new_transition(6, 'a', 4);
    d->func->v[13] = new_transition(6, 'b', 7);
    d->func->v[14] = new_transition(7, 'a', 4);
    d->func->v[15] = new_transition(7, 'b', 7);
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
