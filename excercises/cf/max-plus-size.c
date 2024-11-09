#include<stdio.h>
#include<math.h>

int main() {
    int t, n, oddmax, evmax, a, i, ans;
    scanf("%d", &t);
    while(t--) {
        oddmax=evmax=0;
        scanf("%d", &n);
        for(i=0; i<n; i++) {
            scanf("%d", &a);
            if(i&1) oddmax = fmax(oddmax, a);
            else evmax = fmax(evmax, a);
        }

        ans = fmax(oddmax + n / 2, evmax + (n + 1) / 2);

        printf("%d\n", ans);
    }

    return 0;
}