#include<stdio.h>
#include "uintv.h"

void test_concat_uintv() {
    struct uintv *v1, *v2;

    v1 = new_uintv(1);
    v2 = new_uintv(1);
    v1->v[0] = 1;
    v2->v[0] = 4;

    concat_uintv(v1, v2);

    if (v1->len == 2 && v1->v[1] == 4 && v1->v[0] == 1) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(v1);
    free_uintv(v2);
}

void test_copy_uintv() {
    struct uintv *v1, *v2;

    v1 = new_uintv(2);
    v2 = new_uintv(2);
    v1->v[0] = 1;
    v1->v[1] = 1;
    v2->v[0] = 0;
    v2->v[1] = 4;

    copy_uintv(v1, v2);

    if (v1->v[0] == 0 && v1->v[1] == 4) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(v1);
    free_uintv(v2);
}

void test_eql_uintv() {
    struct uintv *v1, *v2, *v3;

    v1 = new_uintv(2);
    v2 = new_uintv(2);
    v3 = new_uintv(3);
    v1->v[0] = 1;
    v1->v[1] = 1;
    v2->v[0] = 0;
    v2->v[1] = 4;

    if (!eql_uintv(v1, v2)) {
        puts("OK");
    } else {
        puts("KO");
    }

    copy_uintv(v2, v1);
    if (eql_uintv(v1, v2)) {
        puts("OK");
    } else {
        puts("KO");
    }

    if (!eql_uintv(v3, v1)) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(v1);
    free_uintv(v2);
    free_uintv(v3);
}

void test_new_uintv_and_fill() {
    struct uintv *v1;

    v1 = new_uintv_and_fill(3, 2, 3, 4);
    if (v1->v[0] == 2 && v1->v[1] == 3 && v1->v[2] == 4) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(v1);
}

void test_append_uintv() {
    struct uintv *vector;

    vector = new_uintv_and_fill(4, 1, 1, 2, 3);
    append_uintv(vector, 2);
    if (vector->len == 5 && vector->v[4] == 2) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(vector);
}

int main()
{
    test_concat_uintv();
    test_copy_uintv();
    test_eql_uintv();
    test_new_uintv_and_fill();
    test_append_uintv();

    return 0;
}