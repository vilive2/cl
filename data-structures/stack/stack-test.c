#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "stack.h"

int main() {


    STACK stack;
    int el;
    
    if( init_stack(&stack, sizeof(int), 10) ) {
        exit(1);
    }

    if(is_empty(&stack)) {
        printf("stack is empty\n");
    } else {
        top(&stack, &el);
        printf("top: %d\n", el);
    }

    el = 102;
    push(&stack, &el);
    el = 392;
    push(&stack, &el);
    el = 345;
    push(&stack, &el);
    el = 392;
    push(&stack, &el);

    if(is_empty(&stack)) {
        printf("stack is empty\n");
    } else {
        top(&stack, &el);
        printf("top: %d\n", el);
    }

    pop(&stack, &el);
    printf("pop: %d\n", el);

    top(&stack, &el);
    printf("top: %d\n", el);

    return 0;
}