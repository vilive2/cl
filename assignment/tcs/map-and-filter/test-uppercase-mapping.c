#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

char words[1000][64];

int main() {

    int N = 0;
    while(scanf("%s", words[N]) != EOF) N++;

    char *capswords = (char *)map(words, N, 64, 64, uppercase);

    for(int i = 0 ; i < N ; i++) {
        printf("%s\n", capswords + i * 64);
    }

    free(capswords);

    return 0;
}