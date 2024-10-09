#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Malloc(n, type) (type *) malloc( (unsigned) (n * sizeof(type)))
#define Realloc(loc, n, type) (type *) realloc( (char *)(loc), \
                                    (unsigned) (n*sizeof(type)))
void msort(void *, size_t, int (*)(const void *, const void *), int, int);
void sort(void *, size_t, size_t, int (*)(const void *, const void *));

// void printarr(void *arr, int nel, int size, void (*printel)(void *)) {
//     for(int i = 0 ; i < nel ; i++) {
//         printel(arr);
//         printf(", ");
//         arr += size;
//     }

//     printf("\n");
// }

// void print_int(void *a) {
//     printf("%d", *(int *)a);
// }