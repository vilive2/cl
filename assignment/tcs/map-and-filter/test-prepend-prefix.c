#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

char names[1000][64];

int main() {

    int N = 0;
    while(scanf("%[^\n]", names[N]) != EOF) N++, getchar();

    char *names_with_prefix = (char *)map(names, N, 64, 64, prepend_prefix);

    for(int i = 0 ; i < N ; i++) {
        printf("%s\n", names_with_prefix + i * 64);
    }

    free(names_with_prefix);

    return 0;
}