#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void hello(char *name) {
    printf("Hello, %s\n", name);
}

void sayhello(void (*hel)(char *), char *to) {
    hel(to);
    printf("From another world!\n");
}

char *ping(char *url) {
    return "pong!";
}

int isup(char *url, char *(*checker)(char *)) {
    char *resp = checker(url);
    if(!strcmp(resp, "pong!")) {
        return 1;
    }

    return 0;
}

int comp_int(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

void printarr(void *arr, int nel, int size, void (*printel)(void *)) {
    for(int i = 0 ; i < nel ; i++) {
        printel(arr);
        printf(", ");
        arr += size;
    }

    printf("\n");
}

void print_int(void *a) {
    printf("%d", *(int *)a);
}

int main() {
    // hello();
    sayhello(hello, "Me");

    if(isup("me.com", ping)) {
        printf("Website is working!\n");
    } else {
        printf("Website not working!\n");
    }

    printf("%p\n", hello);
    printf("%ld\n", sizeof(hello));

    int a[] = {4, 1, 7, 0, 100, 3};
    qsort(a, 6, sizeof(int), comp_int);

    printarr(a, 6, sizeof(int), print_int);

    return 0;
}