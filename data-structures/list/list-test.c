#include<stdio.h>
#include "list.h"

void printer(const void *el) {
    printf("%d", *(int *)el);
}

int main() {
    LIST l;
    init_list(&l, 1, sizeof(int));
    print_list(&l, printer);

    int el;

    el = 9; append(&l, &el);
    el = 1; append(&l, &el);
    el = 2; append(&l, &el);
    el = 3; append(&l, &el);
    el = 6; append(&l, &el);
    el = 7; append(&l, &el);
    el = 8; append(&l, &el);
    el = 4; append(&l, &el);
    print_list(&l, printer);

    el = 2; append(&l, &el);
    el = 3; append(&l, &el);
    el = 9; insert_at(&l, &el, 0);
    el = 2; insert_at(&l, &el, 0);
    el = 4; insert_at(&l, &el, 0);
    el = 8; insert_at(&l, &el, 0);
    el = 2; insert_at(&l, &el, 0);
    el = 5; insert_at(&l, &el, 0);
    el = 9; insert_at(&l, &el, 0);
    print_list(&l, printer);

    el = 8; insert_at(&l, &el, 0);
    el = 9; insert_at(&l, &el, 0);
    el = 1; insert_at(&l, &el, 0);

    delete_at(&l, l.size - 1);
    delete_at(&l, l.size - 1);
    delete_at(&l, l.size - 1);
    delete_at(&l, l.size - 1);
    delete_at(&l, l.size - 1);
    delete_at(&l, 0);
    print_list(&l, printer);

    delete_at(&l, 0);
    delete_at(&l, 0);
    delete_at(&l, 0);
    delete_at(&l, 0);
    el = 7; deleteall_key(&l, &el);
    el = 2; deleteall_key(&l, &el);
    el = 9; deleteall_key(&l, &el);
    el = 4; deleteall_key(&l, &el);
    el = 7; deleteall_key(&l, &el);
    print_list(&l, printer);

    return 0;
}