#include<stdio.h>
#include<math.h>

typedef unsigned int ui;

ui rev(ui x) {
    ui y = 0;

    while(x) {
        y = (y * 10) + (x % 10);
        x = x / 10;
    }

    return y;
}

void split(ui v, ui *x, ui *y, int m, int n) {
    *x = 0;
    *y = 0;

    char xx[m + 1], yy[n + 1];
    // for(int i = 0 ; i < m ; i++) xx[i] = '0';
    // for(int i = 0 ; i < n ; i++) yy[i] = '0';

    for(int i = n - 1 ; i >= 0 ; i--) {
        yy[i] = '0' + (v % 10);
        v /= 10;
    }

    for(int i = m - 1 ; i >= 0; i--) {
        xx[i] = '0' + (v % 10);
        v /= 10;
    }

    // *x = rev(*x);
    // *y = rev(*y);
    sscanf(xx, "%d", x);
    sscanf(yy, "%d", y);
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    int M = pow(10, m);
    int N = pow(10, n);

    // printf("%d %d \n", M, N);

    ui a[M][N];

    for(int i = 0 ; i < M ; i++) {
        for(int j = 0 ; j < N ; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int got = 0;
    for(ui i = 0 ; i < M ; i++) {
        for(ui j = 0 ; j < N ; j++) {
            ui x, y;
            split(a[i][j], &x, &y, m, n);
            if(x == i && y == j) {
                got = 1;
                printf("%d %d\n", i, j);
            }
            // printf("%d %d %d\n",x, y, a[i][j]);
        }
    }

    if(!got) printf("No treasure found.\n");

    return 0;
}