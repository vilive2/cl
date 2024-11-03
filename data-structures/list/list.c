#include<stdlib.h>
#include<string.h>
#include "list.h"

int list_init(LIST *list, size_t size, size_t esize) {
    list->capacity = size;
    list->esize = esize;
    list->size = size;
    if(NULL == (list->elements = malloc(size*esize))) 
        return -1;

    return 0;
}

int list_append(LIST *list, const void *eptr) {
    if(list->size == list->capacity) {
        list->capacity = 2 * list->capacity;
        if(list->capacity == 0)
            list->capacity = 1;
        if(NULL == (list->elements = realloc(list->elements, 
                list->capacity * list->esize)))
            return -1;
    }

    if( NULL == memcpy(list->elements + list->size * list->esize, eptr, list->esize) ) 
        return -1;

    list->size++;

    return 0;
}

int list_pop(LIST *list, void *eptr) {
    if(list->size == 0) 
        return -1;

    list->size--;
    if(NULL == memcpy(eptr, list->elements + list->size * list->esize, list->esize) ) 
        return -1;

    return 0;
}

int list_get(LIST *list, void *eptr, size_t index) {
    if(list->size <= index) 
        return -1;

    if(NULL == memcpy(eptr, list->elements + index * list->esize, list->esize) ) 
        return -1;

    return 0;
}

int list_set(LIST *list, const void *eptr, size_t index) {
    if(list->size <= index) 
        return -1;

    if(NULL == memcpy(list->elements + index * list->esize, eptr, list->esize) )
        return -1;

    return 0;
}