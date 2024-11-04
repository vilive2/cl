#ifndef _MAP_
#define _MAP_
#define N 1000000

typedef struct pair {
    void *key;
    void *value;
    struct pair *next;
} PAIR;

typedef struct map {
    PAIR **table;
    size_t table_size, key_size, value_size, size;
    size_t (*hash)(const struct map*, const void *);
} MAP;

int map_init(MAP *mp, size_t size, size_t key_size, size_t value_size);
int map_get(MAP *mp, const void *key, void *value);
int map_put(MAP *mp, const void *key, const void *value);
int map_keys(MAP *mp, void *keys);
int map_delete(MAP *mp, const void *key);

#endif // _MAP_