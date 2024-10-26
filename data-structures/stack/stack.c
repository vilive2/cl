#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "stack.h"

int init_stack(STACK *s, int element_size, int capacity) {
    if(s == NULL) return -1;

    if (NULL == (s->elements = malloc(capacity*element_size))) {
        fprintf(stderr, "stack: out of memory\n");
        return -1;
    }
    s->element_size = element_size;
    s->max_elements = capacity;
    s->num_elements = 0;

    return 0;
}

void free_stack(STACK *s) {
    if(s) free(s->elements);
}

bool is_empty(const STACK *s) {
    return s==NULL || s->num_elements == 0;
}

int push(STACK *s, const void *eptr) {
    if(s->num_elements == s->max_elements) {
        fprintf(stderr, "\nOverflow (stack full, num_elements = %lu)\n", s->num_elements);
        return -1;
    }
    memcpy(s->elements + s->num_elements * s->element_size, eptr, s->element_size);
    s->num_elements++;
    return 0;
}

int pop(STACK *s, void *eptr) {
    if(s->num_elements == 0) {
        fprintf(stderr, "\nUnderflow (stack empty)\n");
        return -1;
    }
    s->num_elements--;
    memcpy(eptr, s->elements + s->num_elements * s->element_size, s->element_size);
    return 0;
}

int top(STACK *s, void *eptr) {
    if(s->num_elements == 0) {
        fprintf(stderr, "\n (stack empty)\n");
        return -1;
    }
    
    memcpy(eptr, s->elements + (s->num_elements - 1) * s->element_size, s->element_size);
    return 0;
}
