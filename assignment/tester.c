#include<stdio.h>
#include "map-filter.c"

void f(void *input, void *output) {
    int x = *(int *)input;
    x = x*x;
    *(int *)output = x;
}

int g(void *input) {
    int x = *(int *)input;
    return x < 0;
    // return x % 2 == 0;
}

int main() {
    int a[] = {-1, 3, -8, 2};
    int *r;
    r = map(a, 4, sizeof(int), sizeof(int), f);

    for(int i = 0 ; i < 4 ; i++)
        printf("%d, ", r[i]);
    printf("\n");

    filter(a, 4, sizeof(int), g);
    for(int i = 0 ; i < 4 ; i++)
        printf("%d, ", a[i]);
    printf("\n");

    free(r);
    return 0;
}