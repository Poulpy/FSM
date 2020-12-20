#include "nfa.h"
#include<stdlib.h>

void test_create_empty_language() {
    struct nfa a;

    a = create_empty_language();

    free_nfa(&a);
}

void test_create_empty_string_language() {
    struct nfa a;

    a = create_empty_string_language();

    free_nfa(&a);
}

int main() {
    test_create_empty_language();
    test_create_empty_string_language();

    return EXIT_SUCCESS;
}
