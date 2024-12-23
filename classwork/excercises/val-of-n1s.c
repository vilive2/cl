#include "common.h"

int f(int n) {
    int s = 0;
    while (n--) s += 1 + f(n);
    return s;
}

int main() {

    for(int i = 0 ; i < 5 ; i++) {
        printf("%d %d\n", i, f(i));
    }

    return 0;
}