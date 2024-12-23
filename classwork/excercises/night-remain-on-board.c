#include "common.h"

int x[] = {2,  2,  1, 1, -2, -2, -1, -1};
int y[] = {-1, 1, -2, 2,  1, -1, 2, -2};

int correct_moves(int i, int j, int m, int n, int k) {
    if(i<0 || j<0 || i>=m || j>=n) return 0;
    if(k == 0) return 1;

    int ans = 0;
    for(int ind = 0 ; ind < 8 ; ind++) {
        ans += correct_moves(i+x[ind], j+y[ind], m, n, k-1);
    }

    return ans;
}

int main() {

    int m=4, n=4, i=0, j=0, k=2;

    scanf("%d%d%d%d%d", &m, &n, &i, &j, &k);

    int total_moves = 1<<(k*3);
    int good_moves = correct_moves(i, j, m, n, k);

    double ans = (double)good_moves / total_moves;
    printf("%d/%d = %lf\n", good_moves, total_moves, ans);

    return 0;
}