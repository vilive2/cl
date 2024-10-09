#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

void max_heapify(int *a, int i, int heap_size);
void build_max_heap(int *a, int n);
void swap(int *a, int *b);