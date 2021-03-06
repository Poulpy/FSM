#include <stdio.h>
#include <assert.h>

#include "uintv.h"

void test_new_uintv() {
    struct uintv *v1;

    v1 = new_uintv(0);

    free_uintv(v1);
}

void test_new_uintv_and_fill() {
    struct uintv *v1;

    v1 = new_uintv_and_fill(3, 2, 3, 4);
    assert(v1->v[0] == 2 && v1->v[1] == 3 && v1->v[2] == 4);

    free_uintv(v1);
}

void test_concat_uintv() {
    struct uintv *v1, *v2, *v3;

    v1 = new_uintv_and_fill(1, 1);
    v2 = new_uintv_and_fill(1, 4);

    concat_uintv(v1, v2);

    assert(v1->len == 2 && v1->v[1] == 4 && v1->v[0] == 1);

    v3 = new_uintv(0);
    concat_uintv(v3, v1);
    assert(eql_uintv(v3, v1));

    free_uintv(v1);
    free_uintv(v2);
    free_uintv(v3);
}

void test_copy_uintv() {
    struct uintv *v1, *v2;

    v1 = new_uintv_and_fill(2, 1, 1);
    v2 = new_uintv_and_fill(2, 0, 4);

    copy_uintv(v1, v2);
    assert(v1->v[0] == 0 && v1->v[1] == 4);

    free_uintv(v1);
    free_uintv(v2);
}

void test_eql_uintv() {
    struct uintv *v1, *v2, *v3, *v4, *v5;

    v1 = new_uintv_and_fill(2, 1, 1);
    v2 = new_uintv_and_fill(2, 0, 4);
    v3 = new_uintv(3);
    v4 = new_uintv(0);
    v5 = new_uintv(0);

    assert(!eql_uintv(v1, v2));

    copy_uintv(v2, v1);
    assert(eql_uintv(v1, v2));

    assert(!eql_uintv(v3, v1));

    assert(eql_uintv(v4, v5));

    free_uintv(v1);
    free_uintv(v2);
    free_uintv(v3);
    free_uintv(v4);
    free_uintv(v5);
}

void test_append_uintv() {
    struct uintv *vector;

    vector = new_uintv_and_fill(4, 1, 1, 2, 3);
    append_uintv(vector, 2);
    assert(vector->len == 5 && vector->v[4] == 2);

    free_uintv(vector);
}

void test_clear_uintv() {
    struct uintv *vector, *empty_vector;

    vector = new_uintv_and_fill(2, 2, 2);

    empty_vector = new_uintv(0);
    clear_uintv(vector);
    assert(eql_uintv(vector, empty_vector));

    free_uintv(vector);
    free_uintv(empty_vector);
}

int main()
{
    test_new_uintv();
    test_new_uintv_and_fill();
    test_concat_uintv();
    test_copy_uintv();
    test_eql_uintv();
    test_append_uintv();
    test_clear_uintv();

    return 0;
}