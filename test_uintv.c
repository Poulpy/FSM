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

int main()
{
    test_concat();
    test_copy_uintv();

    return 0;
}