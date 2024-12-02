#ifndef _MAP_
#define _MAP_

typedef struct pair {
    void *key;
    void *value;
    struct pair *next;
} PAIR;

typedef struct map {
    PAIR **table;
    size_t key_size;
    size_t value_size;
    size_t size;
    size_t table_size;
    size_t (*hash)(const struct map*, const void *);
    int (*comp)(const void *, const void *);
} MAP;

int map_init(MAP *mp, size_t key_size, size_t value_size, size_t capacity, int (*comp)(const void *, const void *));
int map_get(MAP *mp, const void *key, void *value);
int map_put(MAP *mp, const void *key, const void *value);
int map_keys(MAP *mp, void *keys);
int map_delete(MAP *mp, const void *key);
void map_print(MAP *mp, void (*printkey)(const void *key, const void *value));

#endif // _MAP_