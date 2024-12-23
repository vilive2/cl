#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main() {

    int counts[26] = {0}, c;

    while((c = getchar()) != EOF) {
        c = tolower(c);
        if(isalnum(c)) {
            counts[c - 'a']++;
        }
    }

    printf("\n\n*************counts are**************\n\n");
    for(int i = 0 ; i < 26 ; i++) {
        if(counts[i] > 0) {
            printf("%c : %d\n", ('a' + i), counts[i]);
        }
    }

    return 0;
}