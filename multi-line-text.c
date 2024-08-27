#include<stdio.h>

int main() {

    char lines[10][81];

    int i = 0, j = 0;
    char c;

    while ((c = getchar()) != EOF) {

        if (c == '\n' || j == 80) {
            
            lines[i][j] = '\0';
            i++;
            j = 0;

        }

        if (i == 10) {
            i--;
            break;
        }

        if(c != '\n') {
            lines[i][j++] = c;
        }
    }

    // print even lines
    for(int j = 0 ; j <= i ; j++) {
        if(j & 1) {
            printf("%s\n", lines[j]);
        }
    }

    return 0;
}