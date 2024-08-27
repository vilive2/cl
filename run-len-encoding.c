#include "common.h"
#include<stdlib.h>

int main(int argc, char *argv[]) {

    char *s, c;
    int size = 0, capacity = 10;
    
    if (s = Malloc(capacity + 1, char) == NULL) {
        fprintf("Failed to allocate memory of capacity: %d bytes", capacity);
        exit(1);
    }

    while ((c = getchar()) != EOF || c != '\n') {

        if (size == capacity) {
            capacity = 2 * capacity;
            
            if (s = Realloc(s, capacity + 1, char) == NULL) {
                fprintf("Failed to allocate memory of capacity: %d bytes", capacity);
                exit(1);
            }
        }

        s[size++] = c;
    }

    s[size] = '\0';

    printf("%s\n", s);

    return 0;
}