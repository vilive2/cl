#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define println printf("\n")

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

void print_point(POINT point) {
    printf("(%.2lf, %.2lf)", point.x, point.y);
}
void print_line(LINE line) {
    printf("[m=%.2lf, c=%.2lf, between points ", line.m, line.c);
    print_point(line.p1);
    printf(" and ");
    print_point(line.p2);
    printf("]");
}

typedef struct {
    double a;
    double b;
} INTERVAL;

void make_line(LINE *line);
double eval(LINE line, double x);
int intersect_interval(LINE *line);
int solve(LINE line1, LINE line2, POINT *sol);
int split_lines_at_xaxis(LINE *lines, int line_count);
double area_bw_lines(LINE line1, LINE line2);

POINT points[10000];
INTERVAL interval;
int m, n;
LINE F[1000];
LINE G[1000];
LINE temp[1000];
int fline_count, gline_count;
LINE xaxis = {
    0, 0, {-inf, 0}, {inf, 0}
};

int main() {
    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++)
        scanf("%lf%lf", &(points[i].x), &(points[i].y));

    scanf("%d", &n);
    for(int i = m ; i < m+n ; i++) 
        scanf("%lf%lf", &(points[i].x), &(points[i].y));

    scanf("%lf%lf", &(interval.a), &(interval.b));

    fline_count = 0;
    for(int i = 0 ; i < m - 1 ; i++) {
        F[fline_count].p1 = points[i];
        F[fline_count].p2 = points[i+1];
        make_line(&F[fline_count]);

        if(intersect_interval(&F[fline_count])) fline_count++;
    }

    gline_count = 0;
    for(int i = m ; i < m+n-1 ; i++) {
        G[gline_count].p1 = points[i];
        G[gline_count].p2 = points[i+1];
        make_line(&G[gline_count]);

        if(intersect_interval(&G[gline_count])) gline_count++;
    }

    int separable = 1;

    if(fmax(points[0].x, points[m].x) > interval.a || fmin(points[m-1].x, points[m+n-1].x) < interval.b) separable = 0;

    for(int i = 0 ; i < fline_count ; i++) {
        POINT sol;
        for(int j = 0 ; j < gline_count ; j++) {
            if(solve(F[i], G[j], &sol)) {
                separable = 0;
                break;
            }
        }

        if(!separable) break;
    }

    if(separable) {
        printf("SEPARABLE\n");
    } else {
        printf("NOT SEPARABLE\n");
    }

    fline_count = split_lines_at_xaxis(F, fline_count);
    gline_count = split_lines_at_xaxis(G, gline_count);

    // for(int i = 0 ; i < fline_count ; i++) {
    //     print_line(F[i]);
    //     println;
    // }

    // for(int i = 0 ; i < gline_count ; i++) {
    //     print_line(G[i]);
    //     println;
    // }

    double area = 0;

    for(int i = 0 ; i < fline_count ; i++) {
        for(int j = 0 ; j < gline_count ; j++) {
            POINT sol;
            if(solve(F[i], G[j], &sol) == 1) {
                LINE l1 = F[i];
                LINE l2 = G[j];
                l1.p2 = sol;
                l2.p2 = sol;
                area += area_bw_lines(l1, l2);
                l1.p1 = sol;
                l1.p1 = sol;
                l1.p2 = F[i].p2;
                l2.p2 = G[j].p2;
                area += area_bw_lines(l1, l2);
            } else 
                area += area_bw_lines(F[i], G[j]);
        }
    }

    printf("%lf\n", area);

    return 0;
}

double area_bw_line_and_xaxis(LINE line) {
    double triangle_area = 0, rectangle_area = 0;

    double width = fabs(line.p1.x - line.p2.x);
    double triangle_height = fabs(line.p1.y - line.p2.y);
    triangle_area = 0.5 * width * triangle_height;

    double rectangle_height = fmin(fabs(line.p1.y), fabs(line.p2.y));
    rectangle_area = width * rectangle_height;

    if(line.p1.y <= 0 && line.p2.y <= 0) 
        return -triangle_area - rectangle_area;

    return triangle_area + rectangle_area;
}

double area_bw_lines(LINE line1, LINE line2) {
    double x1, x2;
    x1 = fmax(line1.p1.x, line2.p1.x);
    x2 = fmin(line1.p2.x, line2.p2.x);
    if(x1 >= x2) return 0;

    line1.p1.x = x1;
    line1.p1.y = eval(line1, x1);
    line1.p2.x = x2;
    line1.p2.y = eval(line1, x2);

    line2.p1.x = x1;
    line2.p1.y = eval(line2, x1);
    line2.p2.x = x2;
    line2.p2.y = eval(line2, x2);

    double area = area_bw_line_and_xaxis(line1) - area_bw_line_and_xaxis(line2);
    return fabs(area);
}

int split_lines_at_xaxis(LINE *lines, int line_count) {
    int temp_count = 0;
    POINT sol;

    for(int i = 0 ; i < line_count ; i++) {
        if(solve(lines[i], xaxis, &sol) == 1) {
            temp[temp_count] = lines[i];
            temp[temp_count+1] = lines[i];
            temp[temp_count].p2 = sol;
            temp[temp_count+1].p1 = sol;
            temp_count += 2;
        } else {
            temp[temp_count++] = lines[i];
        }
    }

    for(int i = 0 ; i < temp_count ; i++) lines[i] = temp[i];

    return temp_count;
}

int intersect_interval(LINE *line) {
    double x1, x2;
    x1 = fmax(line->p1.x, interval.a);
    x2 = fmin(line->p2.x, interval.b);

    if(x1 <= x2) {
        line->p1.x = x1;
        line->p1.y = eval(*line, x1);
        line->p2.x = x2;
        line->p2.y = eval(*line, x2);
        return 1;
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
    x1 = fmax(line1.p1.x, line2.p1.x);
    x2 = fmin(line1.p2.x, line2.p2.x);

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