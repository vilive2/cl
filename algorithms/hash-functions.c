#include<stdio.h>
#include <time.h>
#include <stdlib.h>

const int p = 1e9+7; // a prime number larger than max key
int a; // a random number between [1, p-1]
int b; // a random number between [0, p-1]
int m = 1003; // table size

unsigned int hash(int k) {
    unsigned int h = a % p;
    k = k % p;
    h = (h * k) % p;
    h = (h + b) % p;
    h = h % m;

    return h;
}

int main() {
    srand(time(NULL));
    a = 1 + (rand() % p);
    b = rand() % p;
    int keys[] = {20, 300, 2, 1000, 53, 79};
    
    printf("key : hash(key)\n");
    for(int i = 0 ; i < sizeof(keys) / sizeof(keys[0]) ; i++) {
        printf("%4d: %d\n", keys[i], hash(keys[i]));
    }
    return 0;
}