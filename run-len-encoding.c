#include "common.h"
#include<stdlib.h>

int rev_digit(int n) {
    int res = 0;
    while(n) {
        res = res*10 + (n % 10);
        n /= 10;
    }

    return res;
}

void add_char_count(char *s, int count, int *index) {

    count = rev_digit(count);
    
    while (count) {
        
        s[*index] = '0' + (count % 10);
        
        count /= 10;

        (*index)++;  
    }

}

int main(int argc, char *argv[]) {

    char *s, c;
    int size = 0, capacity = 10;
    
    if ( (s = Malloc(capacity + 1, char)) == NULL) {
        fprintf("Failed to allocate memory of capacity: %d bytes", capacity);
        exit(1);
    }

    while ((c = getchar()) != EOF && c != '\n') {

        if (size == capacity) {
            capacity = 2 * capacity;
            
            if ((s = Realloc(s, capacity + 1, char)) == NULL) {
                fprintf("Failed to allocate memory of capacity: %d bytes", capacity);
                exit(1);
            }
        }

        s[size++] = c;
    }

    s[size] = '\0';

    printf("read line: %s\n", s);

    ////////////////////////////////////////////////////////
    //              ENCODING                              //
    ////////////////////////////////////////////////////////
    
    int enc_size = 0;
    
    /* initialize a char sequence */
    char prev = s[0];
    int char_count = 0;

    /* go through each character including null */
    for(int i = 0 ; i <= size ; i++) {

        if (s[i] == prev) {     /* if same as prev. character */

            char_count++;
        
        } else {            /* otherwise */
            
            s[enc_size++] = prev;
            
            if(char_count > 1) {
                
                add_char_count(s, char_count, &enc_size);

            }

            /* begin new char sequence */
            prev = s[i];
            char_count = 1;
        }
    }

    s[enc_size] = '\0';
    printf("encoded text : %s\n", s);

    ////////////////////////////////////////////////////////
    //              DECODING                              //
    ////////////////////////////////////////////////////////


    return 0;
}