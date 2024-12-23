#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

char emails[1005][128];

int main() {

    scanf("%s", domain);

    int N = 0;
    while(scanf("%s", emails[N]) != EOF) N++;

    filter(emails, N, 128, filter_email);

    for(int i = 0 ; i < N ; i++) {
        printf("%s\n", emails[i] );
    }

    return 0;
}