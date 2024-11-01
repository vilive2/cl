#include<stdio.h>
#include<string.h>

int main() {

    char line[100];
    line[0] = '0';
    int a = 100;
    int l = 0;
    l += sprintf(line, "%d", a);
    l += sprintf(&(line[l]), "%d", a);
    printf("%s\n", line);
    printf("%d\n", l);
    l = strlen(line);
    printf("%d\n", l);

    return 0;
}