#include<stdio.h>
#include<stdlib.h>
#define MAX(a, b) a>b?a:b

int comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {

    int n, l;
    scanf("%d%d", &n, &l);
    
    int a[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), comp);

    double ans = MAX(a[0], l - a[n-1]);

    for(int i = 1; i < n; i++) {
        ans = MAX(ans, (double)(a[i] - a[i-1]) / 2);
    }

    printf("%lf\n", ans);

    return  0;
}