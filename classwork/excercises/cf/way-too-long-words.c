#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {

    int n;
    scanf("%d", &n);
    char s[101];
    size_t m;
    while(n--) {
        scanf("%s", s);
        m = strlen(s);
        if(m > 10) {
            sprintf(s, "%c%ld%c", s[0], m - 2, s[m-1]);
        }

        printf("%s\n", s);
    }

    return 0;
}