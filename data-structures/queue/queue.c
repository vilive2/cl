#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include "queue.h"

int queue_init(QUEUE *q, size_t key_size, size_t capacity) {
    assert(q != NULL);
    assert(key_size != 0);
    assert(capacity != 0);
    
    q->key_size = key_size;
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->back = 0;

    if(NULL == (q->keys = malloc(capacity * key_size)))
        return -1;

    return 0; 
}

int queue_push_back(QUEUE *q, const void *key) {
    if(q->size == q->capacity)
        return -1;

    if(NULL == memcpy(q->keys + q->back * q->key_size, key, q->key_size)) 
        return -1;

    q->size++;
    q->back++;
    if(q->back == q->capacity)
        q->back = 0;

    return 0;
}

int queue_pop_front(QUEUE *q, void *key) {
    if(q->size == 0)
        return -1;

    if( NULL == memcpy(key, q->keys + q->front * q->key_size, q->key_size) ) 
        return -1;

    q->size--;
    q->front++;
    if(q->front == q->capacity)
        q->front = 0;

    return 0;
}

int queue_front(QUEUE *q, void *key) {
    if(q->size == 0)
        return -1;

    if( NULL == memcpy(key, q->keys + q->front * q->key_size, q->key_size) ) 
        return -1;

    return 0;
}

void queue_print(QUEUE *q, void (*printkey)(const void *)) {
    int cur = q->front;
    printf("[");

    for(int i = 0 ; i < q->size ; i++) {
        printkey(q->keys + cur * q->key_size);
        cur = (cur + 1) % q->capacity;
        printf(", ");
    }

    printf("]\n");
}