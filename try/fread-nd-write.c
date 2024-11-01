#include<stdio.h>

int main() {

    int a[] = {1, 2, 3, 4, 5};
    printf("%ld\n", fwrite(a, sizeof(int), 5, stdout));

    fread(a, sizeof(int), 2, stdin);

    for(int i = 0 ; i < 5 ; i++) printf("%d ", a[i]);
    char c = 0;
    printf("\n|%c|\n", c);

    return 0;
}