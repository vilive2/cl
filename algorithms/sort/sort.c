#include "common.h"

void sort(void *base, size_t elcount, size_t elsize, int (*comp)(const void *, const void *)) {
    msort(base, elsize, comp, 0, elcount - 1);    
}

int main() {

    return 0;
}