#include<stdio.h>
#include<ctype.h>

int isvowel(int c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {

    int c, prev = ' ';
    int vowels = 0;
    int words = 0;

    while((c = fgetc(stdin)) != EOF) {
        if(isvowel(c)) {
            vowels++;
        }

        if(!isalnum(c) && isalnum(prev)) {
            words++;
        }

        prev = c;
    }

    if(isalnum(prev)) words++;

    printf("vowels: %d, words: %d\n", vowels, words);

    return 0;
}