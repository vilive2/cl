#ifndef _LIST_
#define _LIST_

typedef struct {
    void *keys;
    size_t key_size;
    size_t size;
    size_t capacity;
} LIST;

int list_init(LIST *list, size_t key_size, size_t size);
int list_append(LIST *list, const void *key);
int list_pop(LIST *list, void *key);
int list_get(LIST *list, void *key, size_t index);
int list_set(LIST *list, const void *key, size_t index);
void list_print(LIST *list, void (*printkey)(const void *));

#endif // _LIST_