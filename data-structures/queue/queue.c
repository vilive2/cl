#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include "queue.h"

int queue_init(QUEUE *q, size_t esize, size_t capacity) {
    q->esize = esize;
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->back = 0;

    if(NULL == (q->elements = malloc(capacity * esize)))
        return -1;

    return 0; 
}

int queue_push_back(QUEUE *q, const void *eptr) {
    if(q->size == q->capacity)
        return -1;

    if(NULL == memcpy(q->elements + q->back * q->esize, eptr, q->esize)) 
        return -1;

    q->size++;
    q->back++;
    if(q->back == q->capacity)
        q->back = 0;

    return 0;
}

int queue_pop_front(QUEUE *q, void *eptr) {
    if(q->size == 0)
        return -1;

    if( NULL == memcpy(eptr, q->elements + q->front * q->esize, q->esize) ) 
        return -1;

    q->size--;
    q->front++;
    if(q->front == q->capacity)
        q->front = 0;

    return 0;
}

int queue_front(QUEUE *q, void *eptr) {
    if(q->size == 0)
        return -1;

    if( NULL == memcpy(eptr, q->elements + q->front * q->esize, q->esize) ) 
        return -1;

    return 0;
}