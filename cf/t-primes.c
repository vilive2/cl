#include<stdio.h>
#include<math.h>

int isprime[1000001];

int main() {

    int n;
    scanf("%d", &n);

    long x;

    for(int i = 0; i < n; i++) {
        scanf("%ld", &x);
        long y = sqrt(x);
        if(y * y == x && isprime(y)) {
            printf("YES\n");
        } else{
            printf("NO\n");
        }
    }

    return 0;
}