#include<stdio.h>
#include<string.h>

int main() {

    char A[] = "lksieukt";
    char B[] = "euskktil";

    int freqA[26] = {0};
    int freqB[26] = {0};

    int N = strlen(A);
    int M = strlen(B);

    for(int i = 0 ; i < N ; i++) {
        freqA[A[i] - 'a']++;
    }

    for(int i = 0 ; i < M ; i++) {
        freqB[B[i] - 'a']++;
    }

    int multiseteq = 1;
    for(int i = 0 ; i < 26 ; i++) {
        if(freqA[i] != freqB[i]) {
            multiseteq = 0 ; 
            break;
        }
    }

    if(multiseteq) {
        printf("'%s' \nand \n'%s' \nare multiset equivalent\n", A, B);
    } else {
        printf("'%s' \nand \n'%s' \nare not multiset equivalent\n", A, B);
    }
    return 0;
}