#include "common.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

////////////////////////////////////////////////////////
//              ENCODING                              //
////////////////////////////////////////////////////////
void encode(char *s) {
    int size = strlen(s);
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
            prev = s[i];
            
            if(char_count > 1) {
                enc_size += sprintf(&s[enc_size], "%d", char_count);
            }

            /* begin new char sequence */
            char_count = 1;
        }
    }

    s[enc_size] = '\0';
}

////////////////////////////////////////////////////////
//              DECODING                              //
////////////////////////////////////////////////////////
void decode(char **p) {
    char *s = *p;
    int size = strlen(s);
    
    char *d = (char *)malloc(size+1);

    int cnt = 0, j = 0, capacity = size;

    for(int i = 0; i <= size; i++) {
        if(isdigit(s[i])) {
            cnt = cnt * 10 + (s[i] - '0');
        } else {
            while(cnt > 1) {
                cnt--;
                if(j == capacity) {
                    capacity = 2*capacity;
                    d = (char *)realloc(d, (capacity + 1));
                }
                d[j] = d[j-1];
                j++;
            }
            cnt = 0;
            if(j == capacity) {
                capacity = 2*capacity;
                d = (char *)realloc(d, (capacity + 1));
            }
            d[j++] = s[i];
        }
    }

    d[j] = '\0';

    free(s);
    *p = d;
}

char max(char *s) {
    // expected s is encoded
    if(s == NULL || s[0] == '\0') {
        return -1;
    }

    char ans = s[0];
    char prev = s[0];
    int cnt = 0, max_cnt = 1;
    s++;
    
    while(*s != '\0') {
        if(isdigit(*s)) {
            cnt = cnt*10 + (*s) - '0';
        } else {
            if(max_cnt < cnt) {
                max_cnt = cnt;
                ans = prev;
            }
            prev = *s;
            cnt = 0;
        }
        s++;
    }

    return ans;
}

int main(int argc, char *argv[]) {

    char *s;
    int c;
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

    encode(s);
    printf("encoded text : %s\n", s);

    printf("most frequent char : %c\n", max(s));

    decode(&s);
    printf("decoded text : %s\n", s);

    return 0;
}