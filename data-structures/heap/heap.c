#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#define LEFT(i) 2*(i)+1
#define RIGHT(i) 2*(i)+2
#define PARENT(i) ((i)-1)/2

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void min_heapify(int *a, int i, int n) {
    int l = LEFT(i), r = RIGHT(i), smallest;

    if(l<n && a[l] < a[i]) smallest = l;
    else smallest = i;

    if(r<n && a[r] < a[smallest]) smallest = r;

    if(smallest != i) {
        swap(&a[i], &a[smallest]);
        min_heapify(a, smallest, n);
    }
}

void make_heap(int *a, int n) {
    for(int i=n/2; i>=0; i--) {
        min_heapify(a, i, n);
    }
}

int minimum(int *a, int n) {
    if(n == 0) {
        fprintf(stderr, "underflow");
        return -1;
    }

    return a[0];
}

int extract_min(int *a, int *n) {
    if(*n == 0) {
        fprintf(stderr, "underflow");
        return -1;
    }

    int min = a[0];
    a[0] = a[(*n)-1];
    *n = (*n) -1;

    min_heapify(a, 0, *n);

    return min;
}

void decrease_key(int *a, int i, int key, int n) {
    if(i<0 || i>=n || key>a[i]) {
        fprintf(stderr, "invalid op");
        return;
    }

    int parent = PARENT(i);
    while(i>0 && a[parent]>key) {
        i = parent;
        parent = PARENT(i);
    }
    a[i] = key;
}

void insert(int **a, int key, int *n, int *cap) {
    if(*n == *cap) {
        *cap = (*cap) * 2;
        *a = (int *)realloc(*a, (*cap) * sizeof(int));
        if(*a == NULL) {
            fprintf(stderr, "memory full");
            return;
        }
    }

    *n = (*n)+1;
    *a[(*n)-1] = INT_MAX;
    decrease_key(*a, (*n)-1, key, *n);
}