#include<stdio.h>
#include<string.h>

int main() {

    char *source = "computing lab";
    char copy[8];
    char b[] = "some other long string";
    strcpy(copy, source);

    printf("%s %s\n", source, copy);

    return 0;
}