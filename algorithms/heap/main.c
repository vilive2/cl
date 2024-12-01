#include<stdio.h>
#include "heap.h"

int main() {

    int a[5] = {10, 3, 2, 100, 5};
    int cap = 5;
    int n = 5;
    make_heap(a, n);
    printf("min: %d \n", minimum(a, n));
    printf("min removed: %d\n", extract_min(a, &n));
    printf("min: %d \n", minimum(a, n));
    
    return 0;
}