#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ERR_MESG(x) { perror(x); exit(1); }
#define swap(a, b, type) {type temp = a; a = b; b = temp;}

#define Malloc(n, type) (type *) malloc( (unsigned) (n * sizeof(type)))
#define Realloc(loc, n, type) (type *) realloc( (char *)(loc), \
                                    (unsigned) (n*sizeof(type)))

#define matrix_alloc(mat,rows,cols,type) {                        \
    int ii;                                                       \
    type *temp;                                                   \
                                                                  \
    if (NULL == (temp = (type *) malloc(rows*cols*sizeof(type))) || \
        NULL == (mat = (type **) malloc(rows * sizeof(type *))))  \
        ERR_MESG("Out of memory");                                \
    for (ii = 0; ii < rows; temp += cols, ii++)                   \
        mat[ii] = temp;                                           \
  }

#define matrix_free(mat) {                      \
    free(mat[0]);                               \
    free(mat);                                  \
  }

void msort(void *, size_t, int (*)(const void *, const void *), int, int);
void sort(void *, size_t, size_t, int (*)(const void *, const void *));

void printarr(void *arr, int nel, int size, void (*printel)(void *)) {
    printf("[");
    for(int i = 0 ; i < nel ; i++) {
        printel(arr);
        if(i+1<nel)
            printf(", ");
        arr += size;
    }

    printf("]\n");
}

void print_int(void *a) {
    printf("%d", *(int *)a);
}