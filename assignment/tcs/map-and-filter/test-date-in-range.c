#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

DATE dates[10000];

int main() {

    int N = 0;
    while(scanf("%d%d%d", &dates[N].date, &dates[N].month, &dates[N].year) != EOF) N++;

    filter(dates, N, sizeof(DATE), date_in_range);

    for(int i = 0 ; i < N ; i++) {
        printf("%02d-%02d-%04d\n", dates[i].date, dates[i].month, dates[i].year);
    }

    return 0;
}