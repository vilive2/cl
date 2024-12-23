#include<stdio.h>
#include "fns.c"
#include "../../map-filter.c"

PERSON person[100000];

int main() {

    int N = 0;
    while(scanf("%s%s%d", person[N].firstname, person[N].lastname, &person[N].age) != EOF) N++;

    char *names = (char *)map(person, N, sizeof(PERSON), 32, person_name);

    if(names == NULL) 
        exit(1);

    for(int i = 0 ; i < N ; i++) {
        printf("%s\n", names + i*32);
    }

    free(names);

    return 0;
}