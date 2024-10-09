#include<stdio.h>
#define N 100000
#define min(a, b) a>b? b:a

typedef long long int bi;

int main() {
    int t, n, q, x[N], i;
    bi k;
    bi ans[N];

    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &q);
        for(i=0; i<n; i++) scanf("%d", &x[i]);
        for(i=0; i<n; i++) ans[i] = 0;

        for(i=0; i<n-1; i++) {
            ans[min(i+1, n-i-1)-1] = x[i+1]-x[i]-1;

            // for boundary points : (n-i)*(i+1)-1 segments
            // others points bw xi and xi+1: (i+1)*(n-i-1) segments 
        }
    }

    return 0;
}