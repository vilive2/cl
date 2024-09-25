#include<stdio.h>

#define LENGTH_SMALL 10
#define LENGTH_LARGE 100

void print_small_array(int input[LENGTH_SMALL], int n) {
    printf("In print_small_array\n");
    for(int i = 0 ; i < n ; i += n/10)
        printf("%d %d\n", i, input[i]);
    printf("\n");
    return;
}

void print_large_array(int input[LENGTH_LARGE], int n) {
    printf("In print_large_array\n");
    for(int i = 0 ; i < n ; i += n / 10)
        printf("%d %d\n", i , input[i]);
    printf("\n");
    return;
}

int main() {

    int *X[10];
    /* int Y[][10]; uncommenting this line generates an error message */
    int (*Z)[10];
    int A[LENGTH_SMALL], B[LENGTH_LARGE], i;

    /* Review question */
    printf("%zd %zd\n", sizeof(X), sizeof(X[0]));
    printf("%zd %zd\n", sizeof(Z), sizeof(Z[0]));

    for(i = 0; i < LENGTH_SMALL; i++) {
        A[i] = i*1000; B[i] = i*10;
    }
    for(; i < LENGTH_LARGE; i++)
        B[i] = i*10;

    for(i = 0; i < LENGTH_SMALL; i++)
        printf("%d %6d %4d\n", i, A[i], B[i]);

    printf("\nPrinting A\n");
    print_small_array(A, LENGTH_SMALL);
    print_large_array(A, LENGTH_SMALL);

    printf("\nPrinting B\n");
    print_small_array(B, LENGTH_LARGE);
    print_large_array(B, LENGTH_LARGE);
    
    return 0;
}