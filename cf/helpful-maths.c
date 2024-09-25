#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int comp(const void *a, const void *b) {
    return ((char *)a)[0] - ((char *)b)[0];
}

int main() {

    char s[102];
    scanf("%s", s);
    int n = strlen(s);
    s[n] = '+';
    s[n+1] = '\0';
    qsort(s, (n + 1) / 2, 2, comp);
    s[n] = '\0';
    printf("%s\n", s);

    return 0;
}