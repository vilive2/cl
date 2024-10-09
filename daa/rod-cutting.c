#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<time.h>

int cut_rod(const int *p, int n, int *s) {
    if(n == 0) {
        return 0;
    }
    int ans = INT_MIN;
    for(int i=0; i<n; i++) {
        int subsol = cut_rod(p, n-i-1, s);
        if(ans < p[i]+subsol) {
            ans = p[i]+subsol;
            s[n]=i+1;
        }
    }

    return ans;
}

void printsol(const int *s, int n) {
    while(n > 0) {
        printf("%d", s[n]);
        n -= s[n];
        if(n != 0) printf(", ");
    }
    printf("\n");
}

int memoized_cut_rod_aux(const int *p, int n, int *r, int *s) {
    if(r[n] >= 0) {
        return r[n];
    }
    int sol = INT_MIN;
    if(n == 0) {
        sol = 0;
    } else {
        for(int i=0; i<n; i++) {
            int subsol = memoized_cut_rod_aux(p, n-i-1, r, s);
            if(sol < p[i]+subsol) {
                sol = p[i]+subsol;
                s[n]=i+1;
            }
        }
    }

    r[n] = sol;
    return sol;
}

int memoized_cut_rod(const int *p, int n, int *s) {
    int r[n+1];
    for(int i=0; i<=n; i++) r[i]=INT_MIN;
    return memoized_cut_rod_aux(p, n, r, s);
}

int bottom_up_cut_rod(const int *p, int n, int *s) {
    int r[n+1];
    r[0] = 0;
    for(int j = 1 ; j <= n; j++) {
        int sol = INT_MIN;
        for(int i = 0 ; i < j ; i++) {
            if(sol < p[i] + r[j - i - 1]) {
                sol = p[i] + r[j-i-1];
                s[j] = i+1;
            }
        }
        r[j] = sol;
    }

    return r[n];
}

int main() {

    int n, p[100], s[100];
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &p[i]);

    printf(" len  profit\n");
    for(int i=0; i<n; i++) printf("%4d %4d\n", i+1, p[i]);
    printf("cutting rod of len %d\n", n);

    clock_t begin = clock();
    int revenue = cut_rod(p, n, s);
    clock_t end = clock();
    int time_spent = (end - begin);
    printf("******simple recursive solution*********\ntime taken:%d ms\n", time_spent);
    printf("Total revenue: %d\nrods of len: ", revenue);
    printsol(s, n);

    printf("******Memoization**********\n");
    begin = clock();
    revenue = memoized_cut_rod(p, n, s);
    end = clock();
    time_spent = end - begin;
    printf("time taken: %d ms\n", time_spent);
    printf("Total revenue: %d\nrods of len: ", revenue);
    printsol(s, n);

    printf("******Bottom UP**********\n");
    begin = clock();
    revenue = bottom_up_cut_rod(p, n, s);
    end = clock();
    time_spent = end - begin;
    printf("time taken: %d ms\n", time_spent);
    printf("Total revenue: %d\nrods of len: ", revenue);
    printsol(s, n);

    return 0;
}