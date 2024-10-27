#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

int init_list(LIST *list, size_t capacity, size_t element_size) {
    list->capacity = capacity;
    list->element_size = element_size;
    list->size = 0;
    if(NULL == (list->elements = malloc(capacity*element_size))) {
        fprintf(stderr, "LIST : INIT, memory allocation failed\n");
        return -1;
    }

    return 0;
}

int append(LIST *list, const void *element) {
    if(list->size == list->capacity) {
        list->capacity = 2 * list->capacity;
        if(NULL == (list->elements = realloc(list->elements, 
                list->capacity * list->element_size))) {
            
            fprintf(stderr, "LIST : APPEND, memory allocation failed\n");
            return -1;
        }
    }

    memcpy(&list->elements[list->size * list->element_size], element, list->element_size);
    list->size++;
    return 0;
}

int insert_at(LIST *list, const void *element, size_t index) {
    if(index >= list->size) {
        fprintf("LIST : INSERT_AT, invalid index:%d\n", index);
        return -1;
    }

    if(list->size == list->capacity) {
        list->capacity = 2 * list->capacity;
        if(NULL == (list->elements = realloc(list->elements, 
                list->capacity * list->element_size))) {
            
            fprintf(stderr, "LIST : INSERT_AT, memory allocation failed\n");
            return -1;
        }
    }

    void *ptr = list->elements + list->size * list->element_size;
    for(int i = list->size - 1 ; i >= (int)index ; i--) {
        memcpy(ptr, ptr - list->element_size, list->element_size);
        ptr -= list->element_size;
    }

    memcpy(ptr, element, list->element_size);
    list->size++;
    return 0; 
}

void print_list(LIST *list, void (*printer)(const void *)) {
    printf("[");
    void *ptr = list->elements;
    for(int i = 0 ; i < list->size ; i++) {
        printer(ptr);
        ptr += list->element_size;
        if(i+1 < list->size) printf(", ");
    }
    printf("]\n");
}

int find(LIST *list, const void *key) {
    void *ptr = list->elements;
    for(int i = 0 ; i < list->size ; i++, ptr += list->element_size) {
        if(!strncmp(ptr, key, list->element_size)) 
            return i;
    }

    return -1;
}

int delete_at(LIST *list, size_t index) {
    if(index >= list->size) {
        fprintf("LIST : DELETE_AT, invalid index:%d\n", index);
        return -1;
    }

    void *ptr = list->elements + index * list->element_size;
    for(int i = index ; i < list->size ; i++) {
        memcpy(ptr, ptr + list->element_size, list->element_size);
        ptr += list->element_size;
    }

    list->size--;

    if(!((list->size + 1) & (list->size))) {
        list->capacity = list->size;
        if(NULL == (list->elements = realloc(list->elements, list->element_size * list->size))) {
            fprintf(stderr, "LIST : DELETE_AT, memory removal failed\n");
            return -1;
        }
    }

    return 0;
}

int deleteall_key(LIST *list, const void *key) {
    void *ptr = list->elements;
    int j = 0;
    for(int i=0; i < list->size ; i++, ptr += list->element_size) {
        if(strncmp(ptr, key, list->element_size)) {
            memcpy(list->elements + j * list->element_size, ptr, list->element_size);
            j++;
        }
    }

    list->size = j;

    if(!((list->size + 1) & (list->size))) {
        list->capacity = list->size;
        if(NULL == (list->elements = realloc(list->elements, list->element_size * list->size))) {
            fprintf(stderr, "LIST : DELETEALL_KEY, memory removal failed\n");
            return -1;
        }
    }

    return 0;
}

int deleteall(LIST *list) {
    list->capacity = 1;
    if(NULL == (list->elements = realloc(list->elements, list->element_size))) {
        fprintf(stderr, "LIST : DELETEALL, memory removal failed\n");
        return -1;
    }
    
    list->size = 0;
}