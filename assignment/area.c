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
double area_bw_lines(LINE line1, LINE line2, POINT *intersection_point);

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

    double area = 0;

    int i = 0, j = m;

    POINT sol;
    LINE line1;
    LINE line2;
    while(i < m-1 && j < m+n-1) {
        line1.p1 = points[i];
        line1.p2 = points[i+1];
        make_line(&line1);

        line2.p1 = points[j];
        line2.p2 = points[j+1];
        make_line(&line2);

        if(solve(line1, line2, &sol) == 1) area += area_bw_lines(line1, line2, &sol);
        else area += area_bw_lines(line1, line2, NULL);

        if(line1.p2.x == line2.p2.x) {
            i++;
            j++;
        } else if(line1.p2.x < line2.p2.x) i++;
        else j++;
    }

    if(fmax(points[0].x, fmax(points[m].x, a)) >= fmin(points[m-1].x, fmin(points[m+n-1].x, b))) {
        printf("UNDEFINED\n");
    } else 
        printf("%.4lf\n", area);

    return 0;
}

double area_bw_line_and_xaxis(LINE line) {
    double triangle_area = 0, rectangle_area = 0;

    double width = line.p2.x - line.p1.x;
    double triangle_height = fabs(line.p1.y - line.p2.y);
    triangle_area = 0.5 * width * triangle_height;

    double rectangle_height = fmin(line.p1.y, line.p2.y);
    rectangle_area = width * rectangle_height;

    return triangle_area + rectangle_area;
}

double area_bw_lines(LINE line1, LINE line2, POINT *intersection_point) {
    
    double area = 0;
    if(intersection_point != NULL) {
        POINT p2 = line1.p2;
        line1.p2 = *intersection_point;
        area += area_bw_lines(line1, line2, NULL);
        line1.p1 = *intersection_point;
        line1.p2 = p2;
        area += area_bw_lines(line1, line2, NULL);
        return area;
    }
    
    double x1, x2;
    x1 = fmax(line1.p1.x, fmax(line2.p1.x, a));
    x2 = fmin(line1.p2.x, fmin(line2.p2.x, b));
    if(x1 >= x2) return 0;

    line1.p1.x = x1;
    line1.p1.y = eval(line1, x1);
    line1.p2.x = x2;
    line1.p2.y = eval(line1, x2);

    line2.p1.x = x1;
    line2.p1.y = eval(line2, x1);
    line2.p2.x = x2;
    line2.p2.y = eval(line2, x2);

    area = area_bw_line_and_xaxis(line1) - area_bw_line_and_xaxis(line2);
    return fabs(area);
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