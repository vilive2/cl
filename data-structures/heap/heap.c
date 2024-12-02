#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include "heap.h"

int heap_init(HEAP *pq, size_t key_size, size_t capacity, int (*comp)(const void *, const void *)) {
    assert(pq != NULL);
    assert(key_size != 0);
    assert(capacity != 0);
    assert(comp != NULL);
    
    pq->key_size = key_size;
    pq->size = 0;
    pq->capacity = capacity;
    pq->comp = comp;

    if(NULL == (pq->keys = malloc(capacity * key_size)))
        return -1;

    return 0;
}

int heap_push(HEAP *pq, const void *eptr) {
    if(pq->size == pq->capacity)
        return -1;

    int i = pq->size;
    int par = (i - 1) / 2;
    void *iptr = pq->keys + i * pq->key_size;
    void *parptr = pq->keys + par * pq->key_size;
    
    while( i>0 && pq->comp(eptr, parptr) < 0 ) {
        if(NULL == memmove(iptr, parptr, pq->key_size))
            return -1;

        i = par;
        par = (i - 1) / 2;
        iptr = parptr;
        parptr = pq->keys + par * pq->key_size;
    }

    if( NULL == memcpy(iptr, eptr, pq->key_size) ) 
        return -1;

    pq->size++;

    return 0;
}

int heapify_down(HEAP *pq, int i) {
    int l = 2 * i + 1, r = 2 * i + 2;
    int child = i;
    if( l < pq->size) {
        if(pq->comp(pq->keys + l * pq->key_size, pq->keys + i * pq->key_size) < 0) 
            child = l;
    }

    if( r < pq->size ) {
        if(pq->comp(pq->keys + r * pq->key_size, pq->keys + child * pq->key_size) < 0) 
            child = r;
    }

    if(child != i) {
        if(NULL == memcpy(pq->keys + pq->size * pq->key_size, pq->keys + i * pq->key_size, pq->key_size))
            return -1;

        if(NULL == memcpy(pq->keys + i * pq->key_size, pq->keys + child * pq->key_size, pq->key_size))
            return -1;
        
        if(NULL == memcpy(pq->keys + child * pq->key_size, pq->keys + pq->size * pq->key_size, pq->key_size))
            return -1;

        return heapify_down(pq, child);
    }

    return 0;
}

int heap_pop(HEAP *pq, void *eptr) {
    if(pq->size == 0)
        return -1;

    if( NULL == memcpy(eptr, pq->keys, pq->key_size) )
        return -1;



    pq->size--;

    if(NULL == memcpy(pq->keys, pq->keys + pq->size * pq->key_size, pq->key_size))
        return -1;

    return heapify_down(pq, 0);
}

int heap_top(HEAP *pq, void *eptr) {
    if(pq->size == 0)
        return -1;

    if( NULL == memcpy(eptr, pq->keys, pq->key_size) )
        return -1;

    return 0;
}

void print_rotated_tree_(HEAP *pq, int root, int spaces, void (*printkey)(const void *), int maxwidth) {
    if(root >= pq->size || spaces > maxwidth) return;
    print_rotated_tree_(pq, 2 * root + 2, spaces + 4, printkey, maxwidth);
    printf("%*s", spaces, "");
    printkey(pq->keys + root * pq->key_size);
    printf("\n");
    print_rotated_tree_(pq, 2 * root + 1, spaces + 4, printkey, maxwidth);
}

void heap_print_rotated(HEAP *pq, void (*printkey)(const void *), int maxwidth) {
    print_rotated_tree_(pq, 0, 0, printkey, maxwidth);
}
