#ifndef _HEAP_
#define _HEAP_

typedef struct {
    void *keys;
    size_t key_size;
    size_t size;
    size_t capacity;
    int (*comp)(const void *, const void *);
} HEAP;

int heap_init(HEAP *pq, size_t key_size, size_t capacity, int (*comp)(const void *, const void *));
int heap_push(HEAP *pq, const void *key);
int heap_pop(HEAP *pq, void *key);
int heap_top(HEAP *pq, void *key);

#endif // _HEAP_