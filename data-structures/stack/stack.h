#ifndef _GSTACK_
#define _GSTACK_

typedef struct {
    void *elements;
    size_t element_size, num_elements, max_elements;
} STACK;

int init_stack(STACK *s, int element_size, int capacity);
void free_stack(STACK *s);
bool is_empty(const STACK *s);
int push(STACK *s, const void *eptr);
int pop(STACK *s, void *eptr);
int top(STACK *s, void *eptr);

#endif // _GSTACK_