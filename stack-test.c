#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "data-structures/stack/stack.h"

int main() {

    STACK stack;
    int el;
    
    if( stack_init(&stack, sizeof(int), 10) ) {
        exit(1);
    }

    el = 102;
    stack_push(&stack, &el);
    el = 392;
    stack_push(&stack, &el);
    el = 345;
    stack_push(&stack, &el);
    el = 392;
    stack_push(&stack, &el);

    
    stack_top(&stack, &el);
    printf("top: %d\n", el);

    stack_pop(&stack, &el);
    printf("pop: %d\n", el);

    stack_top(&stack, &el);
    printf("top: %d\n", el);

    return 0;
}