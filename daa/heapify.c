#include "heap.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void max_heapify(int *a, int i, int heap_size) {
    int largest, l = LEFT(i), r = RIGHT(i);
    if(l <= heap_size && a[l-1] > a[i-1]) {
        largest = l;
    } else {
        largest = i;
    }

    if(r <= heap_size && a[r-1] > a[largest-1]) {
        largest = r;
    }
    if(largest != i) {
        swap(&a[i-1], &a[largest-1]);
        max_heapify(a, largest, heap_size);
    }
}