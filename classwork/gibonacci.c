#include "common.h"

int g_rec(int n) {
    if(n<3) return n;
    return g_rec(n-1)+g_rec(n-2)+g_rec(n-3);
}

int g_itr(int n) {
    if(n<3) return n;
    int g0=0, g1=1, g2=2;
    for(int i=3; i<=n; i++) {
        int gi = g0+g1+g2;
        g0=g1;
        g1=g2;
        g2=gi;
    }

    return g2;
}

int main() {

    for(int i = 0; i < 20; i++) {
        if(g_rec(i) != g_itr(i)) {
            printf("not matching %dth value rec :%d, itr: %d\n", i, g_rec(i), g_itr(i));
            exit(1);
        }
    }

    printf("success!\n");

    return 0;
}