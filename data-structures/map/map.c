#include<stdlib.h>
#include<string.h>
#include "map.h"

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

int map_init(MAP *mp, size_t size, size_t key_size, size_t value_size) {
    if(size > N)
        return -1;

    mp->table_size = next_prime(size);
    mp->key_size = key_size;
    mp->value_size = value_size;
    mp->size = 0;
    mp->hash = _hash;

    if(NULL == (mp->table = (PAIR **)calloc(mp->table_size, sizeof(PAIR *))) )
        return -1;

    return 0;
}

PAIR *map_get_(MAP *mp, const void *key) {

    size_t hash_key = mp->hash(mp, key);

    PAIR *cur = mp->table[hash_key];

    while(cur != NULL) {
        if(strncmp(cur->key, key, mp->key_size) == 0) {
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
        if(strncmp(cur->key, key, mp->key_size) == 0) {
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