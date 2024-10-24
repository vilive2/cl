#include "common.h"

int C(int n, int r) {
    if(n<0 || r<0) ERR_MESG("invalid input"); 
    if(n==r) return 1;
    if(n<r) return 0;
    if(r==0) return 1;
    return C(n-1, r) + C(n-1, r-1);
}

int main() {

    printf("%d \n",C(4, 2));
    printf("%d \n",C(4, 0));
    printf("%d \n",C(4, 1));
    printf("%d \n",C(4, 6));
    printf("%d \n",C(4, -2));

    return 0;
}