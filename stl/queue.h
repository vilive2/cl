#ifndef _QUEUE_
#define _QUEUE_

typedef struct {
    void *elements;
    size_t esize, size, capacity, front, back;
} QUEUE;

int queue_init(QUEUE *q, size_t esize, size_t capacity);
int queue_push_back(QUEUE *q, const void *eptr);
int queue_pop_front(QUEUE *q, void *eptr);
int queue_front(QUEUE *q, void *eptr);

#endif // _QUEUE_