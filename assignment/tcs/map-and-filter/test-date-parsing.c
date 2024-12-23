#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

DATE dates[10000];

int main() {

    int N = 0;
    while(scanf("%d%d%d", &dates[N].date, &dates[N].month, &dates[N].year) != EOF) N++;

    char *formated_dates = (char *)map(dates, N, sizeof(DATE), 16, parse_date);

    if(formated_dates == NULL) 
        exit(1);

    for(int i = 0 ; i < N ; i++) {
        printf("%s\n", formated_dates + i*16);
    }

    free(formated_dates);

    return 0;
}