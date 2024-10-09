#include<stdio.h>
#include<stdlib.h>
#include "../common.h"
#define max(a, b) a>b?a:b
#define N 200000
typedef long long int bi;
int a[N], t, n;

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void merge(int *a, int l, int r) {
    int mid = l + (r - l) / 2;
    int tmp[mid-l+1];
    for(int i = l; i <= mid; i++) tmp[i-l] = a[i];

    int i = 0, j = mid+1, k = l;
    while(i+l<=mid && j<=r) {
        if(tmp[i] < a[j]) a[k++] = tmp[i++];
        else a[k++] = a[j++];
    }
    while(i+l<=mid) a[k++] = tmp[i++];
}

void mmsort(int *a, int l, int r) {
    if(l >= r) return;
    int mid = l + (r - l) / 2;
    mmsort(a, l, mid);
    mmsort(a, mid+1, r);
    merge(a, l, r);
}

int main() {
    scanf("%d", &t);
    while(t--) {
        bi ans = 0;
        scanf("%d", &n);
        
        for(int i = 0 ; i < n ; i++) scanf("%d", &a[i]);
        if(n < 3) ans = -1;
        else{
            // qsort(a, n, sizeof(int), cmp);
            // msort(a, 0, n-1);
            sort(a, n, sizeof(int), cmp);

            bi med = a[n / 2];
            bi sm = 0;
            for(int i = 0 ; i < n ; i++) sm += (bi)a[i];

            bi req = (bi)(2*n)*med + (bi)1;
            ans = max((bi)0 , req - sm );
        }

        printf("%lld\n", ans);
    }
    
    return 0;
}