#include<stdlib.h>
#include<string.h>
#include "stack.h"

int stack_init(STACK *s, size_t esize, size_t capacity) {
    s->esize = esize;
    s->capacity = capacity;
    s->size = 0;
    if (NULL == (s->elements = malloc(capacity*esize))) {
        return -1;
    }

    return 0;
}

int stack_push(STACK *s, const void *eptr) {
    if(s->size == s->capacity)
        return -1;

    memcpy(s->elements + s->size * s->esize, eptr, s->esize);
    s->size++;

    return 0;
}

int stack_pop(STACK *s, void *eptr) {
    if(s->size == 0)
        return -1;

    s->size--;
    memcpy(eptr, s->elements + s->size * s->esize, s->esize);
    
    return 0;
}

int stack_top(STACK *s, void *eptr) {
    if(s->size == 0)
        return -1;

    memcpy(eptr, s->elements + (s->size-1) * s->esize, s->esize);
    
    return 0;
}
