#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include "stack.h"

int stack_init(STACK *s, size_t key_size, size_t capacity) {
    assert(s != NULL);
    assert(key_size != 0);
    assert(capacity != 0);
    
    s->key_size = key_size;
    s->capacity = capacity;
    s->size = 0;
    if (NULL == (s->keys = malloc(capacity*key_size))) {
        return -1;
    }

    return 0;
}

int stack_push(STACK *s, const void *eptr) {
    if(s->size == s->capacity)
        return -1;

    memcpy(s->keys + s->size * s->key_size, eptr, s->key_size);
    s->size++;

    return 0;
}

int stack_pop(STACK *s, void *eptr) {
    if(s->size == 0)
        return -1;

    s->size--;
    memcpy(eptr, s->keys + s->size * s->key_size, s->key_size);
    
    return 0;
}

int stack_top(STACK *s, void *eptr) {
    if(s->size == 0)
        return -1;

    memcpy(eptr, s->keys + (s->size-1) * s->key_size, s->key_size);
    
    return 0;
}

void stack_print(STACK *s, void (*printkey)(const void *)) {
    printf("[\n");

    for(int i = s->size - 1 ; i >= 0 ; i--) {
        printkey(s->keys + i * s->key_size);
        printf("\n");
    }

    printf("]\n");
}