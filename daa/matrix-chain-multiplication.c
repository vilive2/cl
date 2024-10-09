#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define Erorr(msg) {printf("%s\n", msg); exit(1);}

typedef struct {
    unsigned int rows;
    unsigned int columns;
    int **a;
} Matrix;

Matrix *new_matrix(unsigned int rows, unsigned int columns) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->columns = columns;
    if(rows == 0) return mat;
    mat->a = (int **)malloc(rows*sizeof(int *));
    if(columns == 0) return mat;
    mat->a[0] = (int *)malloc(rows*columns*sizeof(int));
    for(int row=1; row<rows; row++) {
        mat->a[row] = &mat->a[row-1][columns];
    }

    return mat;
}

void print_arr(const int *a, unsigned int size) {
    if(a == NULL) return;
    printf("[");
    for(int i=0; i<size; i++) {
        printf("%d", a[i]);
        if(i+1<size) printf(", ");
    }
    printf("]\n");
}

void print_matrix(const Matrix *m) {
    if(m == NULL) return;

    printf("[");
    for(int i=0; i<m->rows; i++) {
        print_arr(m->a[i], m->columns);
    }
    printf("]\n");
}

Matrix *multiply(const Matrix *a, const Matrix *b) {
    if(a->columns != b->rows)
        Erorr("incompatible dimenstions")

    Matrix *res = new_matrix(a->rows, b->columns);

    for(int i = 0; i < res->rows; i++) {
        for(int j = 0; j < res->columns; j++) {
            res->a[i][j]=0;
            for(int k = 0; k < a->columns; k++) {
                res->a[i][j] += a->a[i][k] * b->a[k][j];
            }
        }
 
    }

    return res;
}

Matrix *read_matrix() {
    int rows, columns;
    scanf("%d%d", &rows, &columns);
    Matrix *mat = new_matrix(rows, columns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            scanf("%d", &mat->a[i][j]);
        }
    }

    return mat;
}

void matrix_chain_order(int *p, int n, Matrix *m, Matrix *s) {

    for(int i = 1 ; i <= n ; i++) m->a[i][i] = 0;

    for(int l = 2 ; l <= n ; l++) {
        for(int i = 1 ; i <= n-l+1 ; i++) {
            int j = i + l - 1;
            m->a[i][j] = INT_MAX;
            for(int k = i ; k < j ; k++) {
                int q = m->a[i][k] + m->a[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m->a[i][j]) {
                    m->a[i][j] = q;
                    s->a[i][j] = k;
                }
            }
        }
    }
}

void print_optimal_parens(Matrix *s, int i, int j) {
    if(i == j) printf("A%d", i);
    else {
        printf("(");
        print_optimal_parens(s, i, s->a[i][j]);
        print_optimal_parens(s, s->a[i][j]+1, j);
        printf(")");
    }
}

int main() {

    // Matrix *A = read_matrix();
    // Matrix *B = read_matrix();
    // Matrix *C = multiply(A, B);
    // print_matrix(C);

    int p[1000];
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) scanf("%d", &p[i]);

    Matrix *s = new_matrix(n+1, n+1);
    Matrix *m = new_matrix(n+1, n+1);
    matrix_chain_order(p, n, m, s);

    printf("cost: %d\n", m->a[1][n]);
    print_optimal_parens(s, 1, n);
    printf("\n");

    return 0;
}