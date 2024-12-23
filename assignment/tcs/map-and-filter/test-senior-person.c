#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

PERSON person[100000];

int main() {

    int N = 0;
    while(scanf("%s%s%d", person[N].firstname, person[N].lastname, &person[N].age) != EOF) N++;

    filter(person, N, sizeof(PERSON), senior_person);

    for(int i = 0 ; i < N ; i++) {
        printf("%s %s %d\n", person[i].firstname, person[i].lastname, person[i].age);
    }

    return 0;
}