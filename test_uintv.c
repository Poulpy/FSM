#include<stdio.h>
#include "uintv.h"

void test_concat() {
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

int main()
{
    test_concat();
    test_copy_uintv();
    test_eql_uintv();

    return 0;
}