#include<stdio.h>
#define N 100

typedef struct {
    float real;
    float imz;
} Complex;

typedef Complex F;

F U[N][N];
F UH[N][N];
F UHxU[N][N];
float I[N][N];
int n;

int unitary();
void transpose();
void conjugate();
void multiply();
int identity();
void print_matrix();

int main() {

    for(int i = 0 ; i < N ; i++) {
        for(int j = 0 ; j < N ; j++) {
            if(i == j) I[i][j] = 1;
            else I[i][j] = 0;
        }
    }

    printf("dimension of of NxN matrix: ");
    scanf("%d", &n);
    printf("enter matrix:\n");
    for(int i = 0 ; i < n ; i++) 
        for(int j = 0 ; j < n ; j++) {
            printf("row %d col %d : ", i, j);
            scanf("%f%f", &U[i][j].real, &U[i][j].imz);
    }

    print_matrix();

    if(unitary()) 
        printf("Unitary.\n");
    else
        printf("Not Unitary.\n");

    return 0;
}


void print_matrix() {
    printf("\n\n*************** MATRIX ***************\n");
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            printf("(%f, i%f) ", U[i][j].real, U[i][j].imz);
        }
        printf("\n\n");
    }
}

int unitary() {
    transpose();
    conjugate();
    multiply();
    return identity();
}

void transpose() {
    for(int i = 0 ; i < n ; i++) {
        for(int j = i ; j < n ; j++) {
            UH[i][j] = U[j][i];
            UH[j][i] = U[i][j];
        }
    }
}

void conjugatef(F *el) {
    el->imz = - el->imz;
}

void conjugate() {
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            conjugatef(&UH[i][j]);
        }
    }
}

Complex complex_mult(Complex a, Complex b) {
    Complex res;
    res.real = a.real * b.real - a.imz * b.imz;
    res.imz = a.real * b.imz + a.imz * b.real;
    return res;
}

Complex complex_add(Complex a, Complex b) {
    Complex res;
    res.real = a.real + b.real;
    res.imz = a.imz + b.imz;
    return res;
}

void multiply() {
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            UHxU[i][j].real = 0;
            UHxU[i][j].imz = 0;
            for(int k = 0 ; k < n ; k++) {
                UHxU[i][j] = complex_add(UHxU[i][j], complex_mult(UH[i][k], U[k][j]) );
            }
        }
    }
}

int identity() {
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            if(UHxU[i][j].real != I[i][j] && UHxU[i][j].imz != 0)
                return 0;
        }
    }

    return 1;
}