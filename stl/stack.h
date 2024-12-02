#ifndef _STACK_
#define _STACK_

typedef struct {
    void *keys;
    size_t key_size;
    size_t size;
    size_t capacity;
} STACK;

int stack_init(STACK *s, size_t key_size, size_t capacity);
int stack_push(STACK *s, const void *key);
int stack_pop(STACK *s, void *key);
int stack_top(STACK *s, void *key);
void stack_print(STACK *s, void (*printkey)(const void *));

#endif // _STACK_