#include<stdio.h>
#include<stdlib.h>
#include "avl.h"
#include "stack.h"
#include "queue.h"

int comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void printkey(const void *a) {
    printf("%d", *(int *)a);
}

int main() {
    int x = 100;
    char c;

    QUEUE q;
    queue_init(&q, sizeof(int), 100);
    while(1) {
        scanf("%c", &c);
        switch(c) {
            case 'i':
                scanf("%d", &x);
                queue_push_back(&q, &x);
                break;
            case 'd':
                queue_pop_front(&q, &x);
                printf("poped %d\n", x);
                break;
            case 'f':
                queue_front(&q, &x);
                printf("front %d\n", x);
                break;
            default:
                exit(0);
        }
        getchar();
        printf("QUEUE\n");
        queue_print(&q, printkey);
    }

    STACK st;
    stack_init(&st, sizeof(int), 100);
    while(0) {
        scanf("%c%d", &c, &x);
        switch(c) {
            case 'i':
                stack_push(&st, &x);
                break;
            case 'd':
                stack_pop(&st, &x);
                printf("poped %d\n", x);
                break;
            case 't':
                stack_top(&st, &x);
                printf("top %d\n", x);
                break;
            default:
                exit(0);
        }
        getchar();
        printf("STACK\n");
        stack_print(&st, printkey);
    }



    TREE tree;
    avl_init(&tree, sizeof(int), 100, comp);

    while(0) {
        scanf("%c%d", &c, &x);
        switch(c) {
            case 'i':
                avl_insert(&tree, &x);
                break;
            case 'd':
                avl_delete(&tree, &x);
                break;
            case 's':
                int ind = avl_search(&tree, &x);
                printf("search(%d) : %d\n", x, ind);
                break;
            default:
                exit(0);
        }
        getchar();

        printf("TREE\n");
        avl_print_rotated(&tree, printkey, 200);
    }

    return 0;
}