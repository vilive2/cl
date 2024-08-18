#include<stdio.h>

int main() {

    char c;
    // int c;

    printf("[ ");
    while((c = fgetc(stdin)) != EOF) {
        printf("['%c', %d], ", c, c);
    }
    printf("]\n");

    return 0;
}