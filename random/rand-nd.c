#include<stdio.h>
#include<stdlib.h>

double normal(void) {
    double z = rand();
    return (double)z / RAND_MAX;
}

int main() {
    printf("%lf\n", normal());
    printf("%lf\n", normal());
    printf("%lf\n", normal());
    printf("%lf\n", normal());
    printf("%lf\n", normal());
    printf("%lf\n", normal());
    return 0;
}