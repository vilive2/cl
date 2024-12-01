#ifndef _QUEUE_
#define _QUEUE_

typedef struct {
    void *keys;
    size_t key_size, size, capacity, front, back;
} QUEUE;

int queue_init(QUEUE *q, size_t key_size, size_t capacity);
int queue_push_back(QUEUE *q, const void *key);
int queue_pop_front(QUEUE *q, void *key);
int queue_front(QUEUE *q, void *key);

#endif // _QUEUE_