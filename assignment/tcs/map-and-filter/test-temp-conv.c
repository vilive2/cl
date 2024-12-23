#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

double temp_in_celsius[100000];

int main() {

    int N = 0;
    while(scanf("%lf", &temp_in_celsius[N]) != EOF) N++;

    double *temp_in_fahrenheit = (double *)map(temp_in_celsius, N, sizeof(double), sizeof(double), celsius_to_fahrenheit);

    if(temp_in_fahrenheit == NULL) 
        exit(1);

    for(int i = 0 ; i < N ; i++) {
        printf("%.4lf\n", temp_in_fahrenheit[i]);
    }

    free(temp_in_fahrenheit);

    return 0;
}