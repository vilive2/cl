#include<stdio.h>
#include<stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    int *arr;
} LIST;

LIST create_list(void) {
    LIST new_list;
    new_list.size = 0;
    new_list.arr = NULL;
    return new_list;
}

void print_list(LIST L) {
    printf("[");
    for(int i = 0; i < L.size; i++) {
        printf("%d", L.arr[i]);
        if(i+1 < L.size) {
            printf(", ");
        }
    }
    printf("]\n");
}

LIST append(LIST L, int a) {
    if(L.size == L.capacity) {
        L.arr = (int *) realloc(L.arr, sizeof(int)*2*L.capacity);
        L.capacity = 2*L.capacity;
    } else {
        L.arr = (int *) realloc(L.arr, sizeof(int)*L.capacity);
    }

    L.arr[L.size++] = a;

    return L;
}

LIST prepend(LIST L, int a) {
    if(L.size == L.capacity) {
        L.capacity = 2*L.capacity;
    }
    
    L.arr = (int *) realloc(L.arr, sizeof(int)*L.capacity);

    for(int i = L.size; i > 0; i--) {
        L.arr[i] = L.arr[i - 1];
    }

    L.arr[0] = a;
    L.size++;

    return L;
}

LIST deletelast(LIST L) {
    if(L.size > 0) {
        L.arr = (int *) realloc(L.arr, sizeof(int)*L.capacity);
        L.size--;
    }

    return L;
}

LIST deletefirst(LIST L) {
    if(L.size > 0) {
        L.arr = (int *) realloc(L.arr, sizeof(int)*L.capacity);
        L.size--;
        for(int i = 0 ; i < L.size ; i++) 
            L.arr[i] = L.arr[i+1];
    }

    return L;
}

LIST deleteall(LIST L, int a) {
    if(L.size > 0) {
        int *arr = (int *) malloc(sizeof(int)*L.capacity);
        int i = 0 , j = 0;
        for(; i < L.size ; i++) {
            if(L.arr[i] != a) {
                arr[j++] = L.arr[i];
            }
        }

        L.arr = arr;
        L.size = j;
    }

    return L;
}

int main() {
    LIST l = create_list();
    print_list(l);
    l = append(l, 9);
    l = append(l, 1);
    l = append(l, 2);
    l = append(l, 3);
    l = append(l, 6);
    l = append(l, 7);
    l = append(l, 8);
    l = append(l, 4);
    print_list(l);

    l = append(l, 2);
    l = append(l, 3);
    l = prepend(l, 9);
    l = prepend(l, 2);
    l = prepend(l, 4);
    l = prepend(l, 8);
    l = prepend(l, 2);
    l = prepend(l, 5);
    l = prepend(l, 9);
    print_list(l);

    l = prepend(l, 8);
    l = prepend(l, 9);
    l = prepend(l, 1);
    l = deletelast(l);
    l = deletelast(l);
    l = deletelast(l);
    l = deletelast(l);
    l = deletelast(l);
    l = deletefirst(l);
    print_list(l);

    l = deletefirst(l);
    l = deletefirst(l);
    l = deletefirst(l);
    l = deletefirst(l);
    l = deleteall(l, 7);
    l = deleteall(l, 2);
    l = deleteall(l, 9);
    l = deleteall(l, 4);
    l = deleteall(l, 7);
    print_list(l);

    return 0;
}