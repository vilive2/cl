// #include "common.h"
#include <stdio.h>

int main(int ac, char *av[])
{
    char str0[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char str1[8] = { 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q' };
    char str2[8] = { 'z', 'y', 'x', 'w', 'v', 'u', 't', 's' };
    char *cp;

    cp = &str0[0];
    printf("%p %p %c\n", cp, &cp, *cp);
    printf("%p %p %p\n", &str0[0], &str1[0], &str2[0]);
    printf("%p %p %p\n", &str0[7], &str1[7], &str2[7]);
    printf("%ld\n", sizeof(cp));
    printf("%p \n", &str0);

    char a;
    int i, *ip;
    short int s, *sp;
    cp = &a;
    ip = &i;
    sp = &s;
    printf("%p %p\n", cp, cp+1);
    printf("%p %p\n", ip, ip+1);
    printf("%p %p\n", sp, sp+1);

    char aa[32] = "Introduction", b[32] = "Programming", *ss, *t;
    //                       ^                       ^
    //                       s                       t
    ss = aa; t = b;
    // while (*s++ = *t++);
    do {
        *ss = *t;
        ss++;
        t++;
    } while(*t != '\0');
 
    printf("%s\n", aa);
 
    for(int i = 0 ; i < 10 ; i++) 
    	printf("abcdefghijklmnop\n" + i);
    
    return 0;
}