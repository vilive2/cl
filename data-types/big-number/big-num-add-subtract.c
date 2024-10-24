#include<stdio.h>
#include<string.h>

void strrev(char *s) {
    int i = 0, j = strlen(s) - 1;
    while(i < j) {
        char tmp = s[i];
        s[i++] = s[j];
        s[j--] = tmp;
    }
}

void printnum(char *num) {
    int i = 0;
    while(num[i] == '0') i++;

    if(num[i] == '\0') {
        printf("0\n");
        return;
    }

    printf("%s\n", &num[i]);
}

void add(char *a, char *b, char *res) {
    strrev(a);
    strrev(b);

    int carry = 0;
    int i = 0, j = 0, k = 0;

    while(carry || a[i] != '\0' || b[j] != '\0') {
        int sum = carry;
        if(a[i] != '\0') {
            sum += a[i++] - '0';
        } 
        if(b[j] != '\0') {
            sum += b[j++] - '0';
        }

        res[k++] = '0' + (sum % 10);
        carry = sum / 10;
    }

    res[k] = '\0';
    strrev(a);
    strrev(b);
    strrev(res);
}

void subtract(char *a, char *b, char *res) {
    strrev(a);
    strrev(b);
    int borrow = 0;
    int i = 0, j = 0, k = 0;

    while(a[i] != '\0') {
        int diff = -borrow;
        borrow = 0;
        diff += a[i++] - '0';
        if(b[j] != '\0') {
            diff -= b[j++] - '0';
        }

        if(diff < 0) {
            diff += 10;
            borrow = 1;
        }

        res[k++] = '0' + diff;
    }

    res[k] = '\0';
    strrev(a);
    strrev(b);
    strrev(res);
}

int isless(char *a, char *b) {
    int la = strlen(a), lb = strlen(b);
    if(la < lb) return 1;
    else if (la > lb) return 0;

    return strcmp(a, b) < 0;
}

int main() {

    char a[101], b[101], res[102], op;

    scanf("%s%s%c%c", a, b, &op, &op);

    printnum(a);
    printnum(b);
    printf("%c\n", op);

    if(op == '+') {
        add(a, b, res);
        printnum(res);
    } else if(op == '-') {
        if(isless(a, b)) {
            subtract(b, a, res);
            printf("-");
        }
        else subtract(a, b, res);

        printnum(res);
    } else {
        printf("unsupported operation\n");
    }

    return 0;
}