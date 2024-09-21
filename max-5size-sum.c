#include<stdio.h>
#define MAX(a, b) a>b?a:b

/*
Read a sequence of positive integers
a0 , a1 , a2 , . . . (the length of the sequence will not be known a priori) and determine max i ∑(j =0 to 4) a(i + j)

*/

int main() {

    int maxsum = 0;
    int a0, a1, a2, a3, a4;
    int i = 0;
    
    while(scanf("%d", &a4) != EOF) {
        i++;

        if(i > 4) {
            maxsum = MAX(maxsum, a0+a1+a2+a3+a4);
        }

        // shift
        a0=a1;
        a1=a2;
        a2=a3;
        a3=a4;
        //a4 is free to read next number
    }

    printf("Maximum of sum of 5 is %d\n", maxsum);
    
    return 0;
}