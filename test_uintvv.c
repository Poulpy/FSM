#include<stdio.h>

#include "uintvv.h"

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

int main() {
    test_new_uintvv_and_fill();

    return 0;
}
