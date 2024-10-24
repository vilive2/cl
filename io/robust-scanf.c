#include <ctype.h>
#include <stdio.h>

#define BUF_LEN 128


int main(int ac, char *av[])
{
    int c, d, retval;

    while (1) {
        retval = scanf("%d", &d);
        if (retval > 0) printf("Read %d, return value = %d\n", d, retval);
        else if (retval == 0) {
            puts("Could not read integer");
            if (EOF == (c = getchar())) {
                puts("EOF");
                break;
            }
            else if (isdigit(c)) ungetc(c, stdin);
            else printf("Skipping char %c (ASCII %d)\n", c, c);
        }
        else {
            puts("EOF");
            break;
        }
    }

    return 0;
}
