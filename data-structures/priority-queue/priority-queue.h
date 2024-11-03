#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

typedef struct {
    void *elements;
    size_t esize, size, capacity;
    int (*comp)(const void *, const void *);
} PRIORITY_QUEUE;

int priority_queue_init(PRIORITY_QUEUE *pq, size_t esize, size_t capacity, int (*comp)(const void *, const void *));
int priority_queue_push(PRIORITY_QUEUE *pq, const void *eptr);
int priority_queue_pop(PRIORITY_QUEUE *pq, void *eptr);
int priority_queue_top(PRIORITY_QUEUE *pq, void *eptr);

#endif // _PRIORITY_QUEUE_