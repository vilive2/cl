#include<stdio.h>
#include<string.h>

void strrev(char *s) {
    int i = 0, j = strlen(s) - 1;
    while(i < j) {
        char tmp = s[i];
        s[i++] = s[j];
        s[j--] = tmp;
    }
}

int main() {

    char s[81];

    // fgets(s, 81, stdin); // stops at newline but keeps newline 
    scanf("%s", s); // stops at newline but replace newline with null

    printf("read : %s\n", s);

    strrev(&s);

    printf("reversed : %s\n", s);

    return 0;
}