#include<stdio.h>


int count_reachable_cells(int n, int k) {
    if(k == 0) return 1;
    if(n == 1) return 2*k+1;

    int ans = 0;
    for(int i = 1 ; i <= k ; i++) 
        ans += count_reachable_cells(n-1, k-i);

    ans <<= 1;

    ans += count_reachable_cells(n-1, k);

    return ans;
}

int main() {

    int t;
    scanf("%d", &t);
    while(t--) {
        int n,k;
        scanf("%d%d", &n, &k);
        printf("%d\n", count_reachable_cells(n, k));
    }

    return 0;
}