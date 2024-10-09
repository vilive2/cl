#include<stdio.h>

int f(int x);
int f(int x);

int main() {

    int i, j = 0;
    i = f(j);

    printf("%d\n", i);

    return 0;
}

int f(int x) {
    return x;
}