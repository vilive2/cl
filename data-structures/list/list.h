#ifndef _LIST_
#define _LIST_

typedef struct {
    void *elements;
    size_t capacity, size, esize;
} LIST;

int list_init(LIST *list, size_t size, size_t esize);
int list_append(LIST *list, const void *eptr);
int list_pop(LIST *list, void *eptr);
int list_get(LIST *list, void *eptr, size_t index);
int list_set(LIST *list, const void *eptr, size_t index);

#endif // _LIST_