#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/*
Write a program to determine the roots of a quadratic equation
ax2 + bx +c = 0
. Your program should ask for the values of a, b and c
, and print the roots (real or complex).
*/

/*

example 1. two distinct integer roots
        (x-1)(x+2)

example 2. two distinct real roots
        (i) rational roots
        (x - 1.5)(x + 2.5)

        (ii) irrational roots
        (x - sqrt(5))(x + sqrt(5))

example 3. two distinct complex roots
        (x - (1 + i2))(x - (1 - i2))

example 4. two identical integer roots
        (x - 2)(x - 2)

example 5. tow identical real roots
        (i) rational roots
        (x - 1.5)(x - 1.5)
        
        (ii) irrational roots
        (x - sqrt(5))(x - sqrt(5))

*/

void print_complex(double r, double i) {
    printf("(");
    printf("%lf", r);
    if(i > 0) printf("+i%lf", i);
    else if (i < 0) printf("-i%lf", -i);
    printf(")");
}

int main() {

    // read coeff.
    double a, b, c;
    printf("Enter values of a, b and c in order: ");
    scanf("%lf%lf%lf", &a, &b, &c);

    // check a must not be zero for quadratic equation
    if(a == 0) {
        printf("invalid input");
        exit(1);
    }

    // calculate roots
    double D = b * b - 4 * a * c;
    double twoa = 2 * a;
    double sqrtD;
    double R1, R2;
    double I1, I2;
    if(D > 0) {
        sqrtD = sqrt(D);
        R1 = (-b + sqrtD) / twoa;
        R2 = (-b - sqrtD) / twoa;
        I1 = I2 = 0;
    } else {
        sqrtD = sqrt(-D);
        R1 = R2 = -b / twoa;
        I1 = sqrtD / twoa;
        I2 = -I1;
    }

    // print roots
    printf("Roots are: ");
    print_complex(R1, I1);
    printf(", ");
    print_complex(R2, I2);
    printf("\n");

    return 0;
}