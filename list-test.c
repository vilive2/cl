#include<stdio.h>
#include "data-structures/list/list.h"

void print_list(LIST *l);

int main() {
    LIST l;
    list_init(&l, 0, sizeof(int));

    int el;

    el = 9; list_append(&l, &el);
    el = 1; list_append(&l, &el);
    el = 2; list_append(&l, &el);
    el = 3; list_append(&l, &el);
    el = 6; list_append(&l, &el);
    el = 7; list_append(&l, &el);
    el = 8; list_append(&l, &el);
    el = 4; list_append(&l, &el);
    print_list(&l);

    el = 2; list_append(&l, &el);
    el = 3; list_append(&l, &el);
    print_list(&l);

    el = 239;
    list_set(&l, &el, 2);
    print_list(&l);

    list_pop(&l, &el);
    printf("popped : %d\n", el);
    list_pop(&l, &el);
    printf("popped : %d\n", el);
    list_pop(&l, &el);
    printf("popped : %d\n", el);
    list_pop(&l, &el);
    printf("popped : %d\n", el);
    list_pop(&l, &el);
    printf("popped : %d\n", el);
    list_pop(&l, &el);
    printf("popped : %d\n", el);
    print_list(&l);

    return 0;
}

void print_list(LIST *l) {
    printf("[");
    for(int i = 0 ; i < l->size ; i++) {
        int el;
        list_get(l, &el, i);
        printf("%d", el);
        if(i+1 < l->size)
            printf(", ");
    }

    printf("]\n");
}