#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdio.h>
#include <time.h>
#include "map.h"

const int p = 1e9+7; // a prime number larger than max key
int a; // a random number between [1, p-1]
int b; // a random number between [0, p-1]

int prime(int x) {
    if(x < 2) return 0;
    if(x == 2) return 1;
    for(int i = 2 ; i*i <= x ; i++) 
        if(x % i == 0) return 0;

    return 1;
}

size_t _hash(const MAP *mp, const void *key) {
    size_t hash_key = 0;
    int xp = 1, c;
    for(int i = 0 ; i < mp->key_size ; i++) {
        c = *(char *)(key + i);
        hash_key = (hash_key + (c * xp)) % mp->table_size;
        xp = (2 * xp) % mp->table_size;
    }

    return hash_key;
}

size_t hash(const struct map *mp, const void *key) {
    size_t k = _hash(mp, key);
    size_t h = a % p;
    k = k % p;
    h = (h * k) % p;
    h = (h + b) % p;
    h = h % mp->table_size;

    return h;
}

PAIR *create_pair(MAP *mp, const void *key) {
    PAIR *new_pair = (PAIR *)malloc(sizeof(PAIR));
    if(new_pair != NULL) {
        new_pair->key = malloc(mp->key_size);
        new_pair->value = malloc(mp->value_size);
    }

    return new_pair;
}

int next_prime(int x) {
    while(!prime(x)) x++;
    return x;
}

int map_init(MAP *mp, size_t key_size, size_t value_size, size_t capacity, int (*comp)(const void *, const void *)){
    assert(mp != NULL);
    assert(key_size != 0);
    assert(value_size != 0);
    assert(capacity != 0);
    assert(comp != NULL);

    srand(time(NULL));
    a = 1 + (rand() % p);
    b = rand() % p;

    mp->table_size = next_prime(capacity);
    mp->key_size = key_size;
    mp->value_size = value_size;
    mp->size = 0;
    mp->hash = hash;
    mp->comp = comp;

    if(NULL == (mp->table = (PAIR **)calloc(mp->table_size, sizeof(PAIR *))) )
        return -1;

    return 0;
}

PAIR *map_get_(MAP *mp, const void *key) {

    size_t hash_key = mp->hash(mp, key);

    PAIR *cur = mp->table[hash_key];

    while(cur != NULL) {
        if(mp->comp(cur->key, key) == 0) {
            break;
        }
        cur = cur->next;
    }

    return cur;
}

int map_get(MAP *mp, const void *key, void *value) {
    
    PAIR *node = map_get_(mp, key);

    if(node != NULL) {
        if(NULL == memcpy(value, node->value, mp->value_size) )
            return -1;
        return 1;
    }

    return 0;
}

int map_put(MAP *mp, const void *key, const void *value) {
    
    PAIR *node = map_get_(mp, key);
    if(node == NULL) {
        size_t hash_key = mp->hash(mp, key);
        node = create_pair(mp, key);
        if(node == NULL || NULL == memcpy(node->key, key, mp->key_size) )
            return -1;

        node->next = mp->table[hash_key];
        mp->table[hash_key] = node;
        mp->size++;
    } 

    if(NULL == memcpy(node->value, value, mp->value_size) )
        return -1;

    return 0;
}

int map_keys(MAP *mp, void *keys) {
    for(int i = 0 ; i < mp->table_size ; i++) {
        PAIR *cur = mp->table[i];
        while(cur != NULL) {
            if(NULL == memcpy(keys, cur->key, mp->key_size) )
                return -1;
            keys = keys + mp->key_size;
            cur = cur->next;
        }
    }

    return 0;
}

int map_delete(MAP *mp, const void *key) {
    size_t hash_key = mp->hash(mp, key);

    PAIR *cur = mp->table[hash_key];
    PAIR *prev = NULL;
    
    while(cur != NULL) {
        if(mp->comp(cur->key, key) == 0) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    if(cur == NULL)
        return -1;

    if(prev != NULL)
        prev->next = cur->next;
    else 
        mp->table[hash_key] = cur->next;

    free(cur);

    return 0;
}

void map_print(MAP *mp, void (*printkey)(const void *key, const void *value)) {
    for(int i = 0 ; i < mp->table_size ; i++) {
        printf("%d: [", i);

        PAIR *cur = mp->table[i];
        while(cur != NULL) {
            printkey(cur->key, cur->value);
            cur = cur->next;
            printf(", ");
        }

        printf("]\n");
    }
}