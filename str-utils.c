#include<stdio.h>

size_t strlen1(char *s) {
    size_t len = 0;
    while((*s) != '\0') {
        s++;
        len++;
    }

    return len;
}

int strcmp1(char *s, char *t) {
    size_t m = strlen1(s), n = strlen1(t);
    if(m != n) return 0;
    for(int i = 0; i < m; i++) {
        if(s[i] != t[i]) return 0;
    }

    return 1;
}

int diff_by_one(char *s, char *t) {
    size_t m = strlen1(s), n = strlen1(t);
    if(m != n) return 0;
    int diff = 0;
    for(int i = 0; i < m; i++) {
        if(s[i] != t[i]) diff++;
    }

    return diff == 1;
}

int add(int *a, int n) {
    return 10;
}

int main() {

    int a[10] = {1, 2, 3}, s;
    s = add(s, 5);

    // char *s = "sale", *t = "sale";
    // printf("is one diff :%d\n", diff_by_one(s, t));
    // printf("are same :%d\n", strcmp1(s, t));

    return 0;
}