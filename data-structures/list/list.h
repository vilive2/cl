#ifndef _LISTH_
#define _LISTH_

typedef struct {
    void *elements;
    size_t capacity, size, element_size;
} LIST;

int init_list(LIST *list, size_t capacity, size_t element_size);
int append(LIST *list, const void *element);
int insert_at(LIST *list, const void *element, size_t index);
void print_list(LIST *list, void (*printer)(const void *));
int find(LIST *list, const void *key);
int delete_at(LIST *list, size_t index);
int deleteall_key(LIST *list, const void *key);
int deleteall(LIST *list);

#endif