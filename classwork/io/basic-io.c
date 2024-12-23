#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 128


void multiple_input_loops_getchar()
{
    int c = 0;

    do
        printf("1st round: %d\n", c);
    while (EOF != (c = getchar()));

    do
        printf("2nd round: %d\n", c);
    while (EOF != (c = getchar()));
}

void multiple_input_loops_scanf()
{
    char c = 0;

    do
        printf("1st round: %d\n", c);
    while (EOF != scanf("%c", &c));

    do
        printf("2nd round: %d\n", c);
    while (EOF != scanf("%c", &c));
}

int main(int ac, char *av[])
{
    char *s, buffer1[BUF_LEN], buffer2[BUF_LEN];
    int c, d, retval;

    /* Reading comma separated values: try on test-input-14082024.txt */
    // while (1) {
    //     scanf("%[^,],%[^,],", buffer1, buffer2);
    //     printf("%s\n", buffer1);
    //     printf("%s\n", buffer2);
    //     if (EOF == (c = getchar())) exit(0);
    //     printf("%c %d\n", c, c);
    // }
    /* Comment the following three lines out after trying them out */
    // multiple_input_loops_scanf();
    // multiple_input_loops_getchar();
    // exit(0);
        
    while (1) {
        retval = scanf("%d", &d);
        if (retval > 0) printf("Read %d, return value = %d\n", d, retval);
        else if (retval == 0) {
            puts("Nothing read, trying getchar");
            if (EOF == (c = getchar())) break;
            else {
                printf("Got char %c (ASCII %d)\n", c, c);
                ungetc(c, stdin);
                retval = scanf("%ms", &s);
                printf("Read %s (%lu chars)\n", s, strlen(s));
                free(s);
            }
        }
        else {
            puts("EOF");
            break;
        }
    }

    return 0;
}
