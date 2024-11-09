#include<stdio.h>
#include<ctype.h>
#include<string.h>

void to_lower(char *s) {
    for(; *s != '\0'; s++) *s = tolower(*s);
}

int main() {

    char a[101], b[101];
    scanf("%s%s", a, b);

    to_lower(a);
    to_lower(b);

    int ans = strcmp(a, b);

    if(ans > 0) ans = 1;
    else if(ans < 0) ans = -1;

    printf("%d\n", ans);

    return 0;
}