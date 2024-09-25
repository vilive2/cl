#include "common.h"

int issorted(int *a, size_t size) {
    for(int i = 1; i < size; i++) {
        if(a[i] < a[i-1]) return 0;
    }

    return 1;
}

int uniquify(int *a, size_t size) {
    if(!issorted(a, size)) return -1;

    if(size == 0) return 0;

    int nel = 1;
    for(int i = 1; i < size; i++) {
        if(a[i] != a[nel - 1]) {
            a[nel] = a[i];
            nel++;
        }
    }

    return nel;
}

void check(int *a, size_t size) {
    printarr(a, size, sizeof(int), print_int);
    int new_size = uniquify(a, size);
    if(new_size == -1) {
        printf("not sorted arr\n");
    } else {
        printarr(a, new_size, sizeof(int), print_int);
    }
}

int main() {

    int empty_arr[]={};
    int single[]={5};
    int sorted_arr[] = {1, 5, 5, 6, 7, 8, 8};
    int sorted_arr1[] = {1, 1, 1, 1, 1, 1};
    int arr[] = {43, 3, 980, 0, 0, 2, 3};

    check(empty_arr, 0);
    check(single, 1);
    check(sorted_arr, 7);
    check(sorted_arr1, 6);
    check(arr, 7);
    return 0;
}