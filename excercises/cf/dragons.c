#include<stdio.h>
#include<stdlib.h>

int comp(const void *a, const void *b) {
    return ((int *)a)[0] - ((int *)b)[0];
}

int main() {

    int s, n;
    scanf("%d%d", &s, &n);

    int xy[n][2];

    for(int i = 0; i < n; i++) {
        scanf("%d%d", &xy[i][0], &xy[i][1]);
    }

    qsort(xy, n, 2*sizeof(int), comp);
    char *ans = "YES";

    for(int i = 0 ; i < n ; i++) {
        if(xy[i][0] >= s) {
            ans = "NO";
            break;
        }
        s += xy[i][1];
    }

    printf("%s\n", ans);

    return 0;
}