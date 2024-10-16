#include "common.h"


void permute(int *A, int k, int n) {
    if(k == n) {
        printarr(A, n, sizeof(int), print_int);
        return;
    }

    for(int i = k ; i < n ; i++) {
        swap(A[i], A[k], int);
        permute(A, k+1, n);
        swap(A[i], A[k], int);
    }
}

int main() {

    int a[] = {1, 2, 3, 4};
    permute(a, 0, 4);
}