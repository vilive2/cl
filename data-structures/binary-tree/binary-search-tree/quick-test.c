#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../binary-tree.h"


typedef struct {
    int x;
} tmp;

int main() {

    char line[100];
    line[0] = '0';
    int a = 100;
    int l = 0;
    l += sprintf(line, "%d", a);
    l += sprintf(&(line[l]), "%d", a);
    printf("%s\n", line);
    printf("%d\n", l);
    l = strlen(line);
    printf("%d\n", l);

    TREE t;
    // t.nodelist = (TNODE *)malloc(16);
    
    if(init_tree(&t, 2)) {
        exit(1);
    }

    int capacity = 3;
    size_t next_size = capacity * sizeof(TNODE);
    printf("\n next cap: %d * %ld\n", capacity, sizeof(TNODE));


    if(NULL == (t.nodelist = (TNODE *)realloc(t.nodelist, next_size))) {
        exit(1);
    }

    // tmp *ptr;
    // ptr = malloc(4);

    // ptr = realloc(ptr, 8);


    t.nodelist[0].data = 1;

    // t.nodelist = (TNODE *)realloc(&(t.nodelist[0]), next_size);
    t.nodelist[1].data = 2;

    printf("\n%d %d\n", t.nodelist[0].data, t.nodelist[1].data);

    return 0;
}