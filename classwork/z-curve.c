#include "common.h"

void printzcurve(int **a, int i, int j, int l) {
    if(l == 1) {
        printf("%d ", a[i][j]);
        return;
    }
    l = l / 2;
    printzcurve(a, i, j, l);
    printzcurve(a, i, j+l, l);
    printzcurve(a, i+l, j, l);
    printzcurve(a, i+l, j+l, l);
}

int main() {

    int **a, l, m;
    scanf("%d", &m);
    l = 1<<m;
    matrix_alloc(a,l,l,int);

    for(int i = 0 ; i < l ; i++) {
        for(int j = 0 ; j < l ; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printzcurve(a, 0, 0, l);
    return 0;
}