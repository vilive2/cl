#include<stdlib.h>
#include<string.h>
#include "priority-queue.h"

int priority_queue_init(PRIORITY_QUEUE *pq, size_t esize, size_t capacity, int (*comp)(const void *, const void *)) {
    pq->esize = esize;
    pq->size = 0;
    pq->capacity = capacity;
    pq->comp = comp;

    if(NULL == (pq->elements = malloc(capacity * esize)))
        return -1;

    return 0;
}

int priority_queue_push(PRIORITY_QUEUE *pq, const void *eptr) {
    if(pq->size == pq->capacity)
        return -1;

    int i = pq->size;
    int par = (i - 1) / 2;
    void *iptr = pq->elements + i * pq->esize;
    void *parptr = pq->elements + par * pq->esize;
    
    while( i>0 && pq->comp(eptr, parptr) < 0 ) {
        if(NULL == memmove(iptr, parptr, pq->esize))
            return -1;

        i = par;
        par = (i - 1) / 2;
        iptr = parptr;
        parptr = pq->elements + par * pq->esize;
    }

    if( NULL == memcpy(iptr, eptr, pq->esize) ) 
        return -1;

    pq->size++;

    return 0;
}

int heapify(PRIORITY_QUEUE *pq, int i, const void *keyptr) {

    void *lptr, *rptr, *iptr, *childptr;
    iptr = pq->elements + i * pq->esize;

    while(1) {

        int l = 2*i + 1;
        int r = 2*i + 2;
        int child = i;

        if(l < pq->size)
            lptr = pq->elements + l * pq->esize;

        if(r < pq->size)
            rptr = pq->elements + r * pq->esize;

        childptr = lptr;

        if( l < pq->size && pq->comp(lptr, keyptr) < 0 )
            child = l;
        else 
            childptr = iptr;

        if(r < pq->size && pq->comp(rptr, childptr) < 0 ) {
            child = r;
            childptr = rptr;
        }

        if( child != i ) {
            if( NULL == memmove(iptr, childptr, pq->esize) )
                return -1;
        } else 
            break;

        i = child;
        iptr = childptr;
    }

    if( NULL == memcpy(iptr, keyptr, pq->esize) )
        return -1;

    return 0;
}

int priority_queue_pop(PRIORITY_QUEUE *pq, void *eptr) {
    if(pq->size == 0)
        return -1;

    if( NULL == memcpy(eptr, pq->elements, pq->esize) )
        return -1;

    pq->size--;

    return heapify(pq, 0, pq->elements + pq->size * pq->esize);
}

int priority_queue_top(PRIORITY_QUEUE *pq, void *eptr) {
    if(pq->size == 0)
        return -1;

    if( NULL == memcpy(eptr, pq->elements, pq->esize) )
        return -1;

    return 0;
}