#include<stdio.h>
#include<stdlib.h>

typedef struct {
    double m;
    double c;
} LINE;

double max(double x, double y) {
    return x>y?x:y;
}
double min(double x, double y) {
    return x>y?y:x;
}

double eval(LINE *l, double x) {
    return l->m * x + l->c;
}

int solve(LINE *l1, LINE *l2, double *x, double *y) {
    if(l1->m == l2->m && l1->c == l2->c) return 0;
    
    if(l1->m == l2->m) {
        double y1 = eval(l1, 0);
        double y2 = eval(l2, 0);
        if(y1 > y2) return 1;
        else return -1;
    }

    *x = (l2->c - l1->c) / (l1->m - l2->m);

    *y = eval(l1, *x);

    return 2;
}

void make_line(LINE *l, double x1, double y1, double x2, double y2) {
    l->m = (y2 - y1) / (x2 - x2);
    l->c = y2 - l->m * x2;
}

void merge(double *a, double *b, int *p, double ca, double cb, int cp) {
    if(*b == ca && *p == cp) {
        *b = cb;
    } else {
        *a = ca;
        *b = cb;
        *p = cp;
    }
}

int main() {

    int m, n;
    scanf("%d", &m);

    double fx[100], fy[100];
    double gx[100], gy[100];

    for(int i = 0 ; i < m ; i++) {
        scanf("%lf%lf", &fx[i], &fy[i]);
    }

    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        scanf("%lf%lf", &gx[i], &gy[i]);
    }

    // printf("%d %d mn\n", m, n);

    // for(int i = 0 ; i < m ; i++) printf("%lf %lf ", fx[i], fy[i]);
    // printf("\n");

    // for(int i = 0 ; i < n ; i++) printf("%lf %lf ", gx[i], gy[i]);
    // printf("\n");

    // exit(1);

    double x[m + n];
    int k = 0, i = 0, j = 0;
    while(i < m && j < n) {
        if(fx[i] < gx[j]) {
            x[k++] = fx[i++];
        } else if(gx[j] < fx[i]) {
            x[k++] = gx[j++];
        } else {
            x[k++] = fx[i++];
            j++;
        }
    }

    while(i < m) x[k++] = fx[i++];
    while(j < n) x[k++] = gx[j++];

    int xlen = k;

    
    // check x's
    // for(int i = 0; i < xlen ; i++) printf("%lf ", x[i]);
    // printf("\n");


    double ma= 1, mb=0;
    double ca, cb;
    int cp = -2;

    int fi = 0, gi = 0;

    for(int i = 0 ; i + 1 < xlen; i++) {
        while(fi < m && fx[fi] <= x[i]) fi++;
        while(gi < n && gx[gi] <= x[i]) gi++;

        if(fi == m || gi == n) break;
        if(fi == 0 || gi == 0) continue;

        double ox1 = max(fx[fi-1], max(x[i], gx[gi - 1]));
        double ox2 = min(fx[fi], min(x[i+1], gx[gi]));

        LINE l1, l2;
        make_line(&l1, fx[fi-1], fy[fi-1], fx[fi], fy[fi]);
        make_line(&l2, gx[gi-1], gy[gi-1], gx[gi], gy[gi]);

        double cx, cy;
        int slv = solve(&l1, &l2, &cx, &cy);
        // printf("%lf %lf %d slv\n ", ox1, ox2, slv);

        if(slv == 0) continue;
        else if(slv == 1) {
            merge(&ca, &cb, &cp, ox1, ox2, slv);
        } else if(slv == -1) {
            merge(&ca, &cb, &cp, ox1, ox2, slv);
        } else {
            double y1, y2;
            y1 = eval(&l1, ox1);
            y2 = eval(&l2, ox1);

            if(y1 > y2) {
                slv = 1;
            } else {
                slv = -1;
            }
            merge(&ca, &cb, &cp, ox1, min(ox2, cx), slv);
            if(cb - ca > mb - ma) {
                mb = cb;
                ma = ca;
            }
            if(cx < ox2)
                merge(&ca, &cb, &cp, cx, ox2, -slv);

        }

        if(cb - ca > mb - ma) {
            mb = cb;
            ma = ca;
        }
    }

    if(ma> mb)
        printf("None\n");
    else
        printf("%lf %lf\n", ma, mb);

    return 0;
}