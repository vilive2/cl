#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    char *source = "computing"; // Allocates 10 bytes
    char *copy = (char *) malloc(strlen(source));
    strcpy(copy, source); // source is larger than copy
    printf("%s\n", copy);
    // free(copy);
    return 0;
}