#include "heap.h"

void build_max_heap(int *a, int n) {
    int heap_size = n;
    for(int i = (n/2) + 1; i > 0; i--) {
        max_heapify(a, i, heap_size);
    }
}