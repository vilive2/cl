#include<stdio.h>
#include<stdlib.h>
#include<math.h>

const int inf = 1e9;

typedef struct {
    double x;
    double y;
} POINT;

typedef struct {
    double m;
    double c;
    POINT p1;
    POINT p2;
} LINE;

void make_line(LINE *line);
double eval(LINE line, double x);
int solve(LINE line1, LINE line2, POINT *sol);

POINT points[100000];
double a, b;
int m, n;

int main() {
    double minx = 0, miny = 0;

    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++)
        scanf("%lf%lf", &(points[i].x), &(points[i].y));

    scanf("%d", &n);
    for(int i = m ; i < m+n ; i++) 
        scanf("%lf%lf", &(points[i].x), &(points[i].y));

    for(int i = 0 ; i < m + n ; i++) {
        minx = fmin(minx, points[i].x);
        miny = fmin(miny, points[i].y);
    }

    scanf("%lf%lf", &a, &b);
    minx = fmin(minx, a);

    minx = fabs(minx);
    miny = fabs(miny);
    for(int i = 0 ; i < m + n ; i++) {
        points[i].x += minx;
        points[i].y += miny;
    }
    a += minx;
    b += minx;

    int separable = 1;
    
    if(fmax(points[0].x, points[m].x) > a || fmin(points[m-1].x, points[m+n-1].x) < b) separable = 0;

    int i = 0, j = m;

    POINT sol;
    LINE line1;
    LINE line2;
    while(i < m-1 && j < m+n-1 && separable) {
        line1.p1 = points[i];
        line1.p2 = points[i+1];
        make_line(&line1);

        line2.p1 = points[j];
        line2.p2 = points[j+1];
        make_line(&line2);

        if(solve(line1, line2, &sol)) separable = 0;

        if(line1.p2.x == line2.p2.x) {
            i++;
            j++;
        } else if(line1.p2.x < line2.p2.x) i++;
        else j++;
    }

    if(separable) {
        printf("SEPARABLE\n");
    } else {
        printf("NOT SEPARABLE\n");
    }

    return 0;
}

void make_line(LINE *line) {
    line->m = (line->p1.y - line->p2.y) / (line->p1.x - line->p2.x);
    line->c = line->p1.y - line->m * line->p1.x;
}

double eval(LINE line, double x) {
    return line.m * x + line.c;
}

int solve(LINE line1, LINE line2, POINT *sol) {
    double x1, x2;
    x1 = fmax(line1.p1.x, fmax(line2.p1.x, a));
    x2 = fmin(line1.p2.x, fmin(line2.p2.x, b));

    if(x1 > x2) return 0;
    
    if(line1.m == line2.m) {
        if(line1.c != line2.c) return 0;
        else if(x1 <= x2) return inf;
        else return 0;
    }

    sol->x = (line2.c - line1.c) / (line1.m - line2.m);
    sol->y = line1.m * sol->x + line1.c;

    if(sol->x >= x1 && sol->x <= x2) return 1;

    return 0;
}