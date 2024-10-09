#include "heap.h"

void heapsort(int *a, int n) {
    build_max_heap(a, n);
    int heap_size = n;
    for(int i = n; i > 1; i--) {
        swap(&a[i-1], &a[0]);
        heap_size = heap_size - 1;
        max_heapify(a, 1, heap_size);
    }
}