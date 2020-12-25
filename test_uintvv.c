#include<stdio.h>

#include "uintvv.h"

void test_new_unitvv() {
}

void test_new_uintvv_and_fill() {
    struct uintvv *m;

    m = new_uintvv_and_fill(2, 2, 1, 9, 3, 4);

    if (m->vv[0]->v[0] == 1 && m->vv[0]->v[1] == 9 && m->vv[1]->v[0] == 3
        && m->vv[1]->v[1] == 4) {

        puts("OK");
    } else {
        puts("KO");
    }

    free_uintvv(m);
}

void test_get_index_uintvv() {
    struct uintvv *m;
    struct uintv *v1, *v2, *v3;

    m = new_uintvv_and_fill(2, 2, 1, 9, 3, 4);
    v1 = new_uintv_and_fill(2, 1, 9);
    v2 = new_uintv_and_fill(2, 3, 4);
    v3 = new_uintv_and_fill(2, 9, 3);

    if (get_index_uintvv(m, v1) == 0) {
        puts("OK");
    } else {
        puts("KO");
    }
    if (get_index_uintvv(m, v2) == 1) {
        puts("OK");
    } else {
        puts("KO");
    }
    if (get_index_uintvv(m, v3) == m->len) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintvv(m);
    free_uintv(v1);
    free_uintv(v2);
    free_uintv(v3);
}

void test_append_uintvv() {
    struct uintvv *m, *empty_matrix;
    struct uintv *v;

    m = new_uintvv_and_fill(2, 2, 3, 4, 5, 6);
    v = new_uintv_and_fill(5, 3, 4, 1, 1, 1);
    append_uintvv(m, v);
    empty_matrix = new_uintvv(0, 0);
    append_uintvv(empty_matrix, v);

    if (empty_matrix->len == 1 && eql_uintv(empty_matrix->vv[0], v)) {
        puts("OK");
    } else {
        puts("KO");
    }

    if (m->len == 3 && eql_uintv(m->vv[2], v)) {
        puts("OK");
    } else {
        puts("KO");
    }

    free_uintv(v);
    free_uintvv(m);
    free_uintvv(empty_matrix);
}

int main() {
    test_new_uintvv_and_fill();
    test_get_index_uintvv();
    test_append_uintvv();

    return 0;
}
