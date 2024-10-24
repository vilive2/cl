#include<stdio.h>
#include<string.h>

int main() {

    char str0[] = {'C', 'o', 'm', 'p', 'u', 't', 'i', 'n', 'g', 'L', 'a', 'b', '\0'};
    char str1[20] = {'C', 'o', 'm', 'p', 'u', 't', 'i', 'n', 'g', 'L', 'a', 'b'};
    char *str2 = "Computing Lab";
    char str3[] = "Computing Lab";
    char str4[30] = "Computing Lab";

    /* Permitted operations */
    str2 = "Another string";
    str2++; 
    str3[0] = 'c';
    strcat(str4, str3); // strcpy also works

    /* NOT permitted */
    // str2[i] = 'X'
    // strcat(str2, str3);
    // str3++; str4++;
    // str3 = "Another string" // reassigning the array variable
    // str4 = "Another string"

    printf("%s\n", str0);
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);

    return 0;
}