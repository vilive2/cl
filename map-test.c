#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "data-structures/map/map.h"

size_t hash(const MAP *mp, const void *key) {
    size_t hash_key = 0;
    int xp = 1, c;
    int key_size = strlen(key);
    for(int i = 0 ; i < key_size ; i++) {
        c = *(char *)(key + i);
        hash_key = (hash_key + (c * xp)) % mp->table_size;
        xp = (2 * xp) % mp->table_size;
    }

    return hash_key;
}

int main() {

    MAP mp;
    if(map_init(&mp, 1000, 100, sizeof(int)) ) {
        fprintf(stderr, "failed to init\n");
        exit(1);
    }

    mp.hash = hash;

    char word[10000];
    int word_size = 0;
    int c;

    while(EOF != (c = fgetc(stdin))) {
        if(isalpha(c))
            word[word_size++] = c;
        else if(word_size > 0) {
            int cnt = 0;
            word[word_size] = '\0';
            // printf("%s \n", word);
            if(map_get(&mp, word, &cnt)) {
                fprintf(stderr, "failed to get\n");
                exit(1);
            }
                
            cnt++;
            if(map_put(&mp, word, &cnt)) {
                fprintf(stderr, "failed to put\n");
                exit(1);
            }

            word_size = 0;
        } 
    }

    if(map_keys(&mp, word) ) {
        fprintf(stderr, "failed to get keys\n");
        exit(1);
    }

    char *key = word;
    printf("total words : %ld\n", mp.size);
    for(int i = 0 ; i < mp.size ; i++) {
        int cnt = 0;
        if(map_get(&mp, key, &cnt)) {
            fprintf(stderr, "failed to get\n");
            exit(1);
        }
        printf("%s : %d\n", key, cnt);
        key = key + mp.key_size;
    }

    return 0;
}