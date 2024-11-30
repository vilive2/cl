#ifndef _STACK_
#define _STACK_

typedef struct {
    void *elements;
    size_t esize, size, capacity;
} STACK;

int stack_init(STACK *s, size_t esize, size_t capacity);
int stack_push(STACK *s, const void *eptr);
int stack_pop(STACK *s, void *eptr);
int stack_top(STACK *s, void *eptr);

#endif // _STACK_