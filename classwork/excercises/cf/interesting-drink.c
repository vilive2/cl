#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int lower_bound(int *a, int n, int x) {
    int l = 0, h = n;
    while(l <= h) {
        int mid = l + (h - l) / 2;
        if(a[mid] < x) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    return l;
}

int upper_bound(int *a, int n, int x) {
    int l = 0, h = n;
    while(l < h) {
        int mid = l + (h - l) / 2;
        if(a[mid] <= x) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }

    return h;
}

int main() {

    int n;
    scanf("%d", &n);

    int x[n];
    for(int i = 0; i < n; i++) scanf("%d", &x[i]);

    int q;
    scanf("%d", &q);

    int m[q];
    for(int i = 0; i < q; i++) scanf("%d", &m[i]);

    qsort(x, n, sizeof(int), cmp);

    for(int i = 0; i < q; i++) {
        int ans = upper_bound(x, n, m[i]);
        printf("%d\n", ans);
    }

    return 0;
}