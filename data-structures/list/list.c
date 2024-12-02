#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include "list.h"

int list_init(LIST *list, size_t key_size, size_t size) {
    assert(list != NULL);
    assert(key_size != 0);
    
    list->capacity = 1 + size;
    list->key_size = key_size;
    list->size = size;
    if(NULL == (list->keys = malloc(list->capacity*key_size))) 
        return -1;

    return 0;
}

int list_append(LIST *list, const void *key) {
    if(list->size == list->capacity) {
        list->capacity = 2 * list->capacity;
        if(list->capacity == 0)
            list->capacity = 1;
        if(NULL == (list->keys = realloc(list->keys, 
                list->capacity * list->key_size)))
            return -1;
    }

    if( NULL == memcpy(list->keys + list->size * list->key_size, key, list->key_size) ) 
        return -1;

    list->size++;

    return 0;
}

int list_pop(LIST *list, void *key) {
    if(list->size == 0) 
        return -1;

    list->size--;
    if(NULL == memcpy(key, list->keys + list->size * list->key_size, list->key_size) ) 
        return -1;

    return 0;
}

int list_get(LIST *list, void *key, size_t index) {
    if(list->size <= index) 
        return -1;

    if(NULL == memcpy(key, list->keys + index * list->key_size, list->key_size) ) 
        return -1;

    return 0;
}

int list_set(LIST *list, const void *key, size_t index) {
    if(list->size <= index) 
        return -1;

    if(NULL == memcpy(list->keys + index * list->key_size, key, list->key_size) )
        return -1;

    return 0;
}

void list_print(LIST *list, void (*printkey)(const void *)) {
    printf("[");

    for(int i = 0 ; i < list->size ; i++) {
        printkey(list->keys + i * list->key_size);
        printf(", ");
    }

    printf("]\n");
}