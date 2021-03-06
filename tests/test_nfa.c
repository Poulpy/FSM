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

void test_create_language_from_char() {
    struct nfa a;

    a = create_language_from_char('c');
    free_nfa(&a);
}

void test_print_nfa() {
    struct nfa a;

    a = create_language_from_char('c');
    print_nfa(&a);
    free_nfa(&a);
}

int main() {
    test_create_empty_language();
    test_create_empty_string_language();
    test_create_language_from_char();
    test_print_nfa();

    return EXIT_SUCCESS;
}
