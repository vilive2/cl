#include<stdio.h>
#include<ctype.h>

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a%b);
}

int ok(int alpha[26], int diz[10], int uns) {
    int sm = 0;
    for(int i = 0; i < 26; i++) sm += alpha[i];
    for(int i = 0; i < 10; i++) sm += diz[i];
    sm += uns;

    return sm == 0;
}

int play(char *s, char *g) {
    int diz[10] = {0}, alpha[26] = {0}, uns = 0;
    for(int i = 0; i < 26; i++) alpha[i] = 0;
    for(int i = 0; i < 10; i++) diz[i] = 0;

    while(*s != '\0') {
        int c = tolower(*s);
        if(isalpha(c)) alpha[c - 'a']++;
        else if(isdigit(c)) diz[c - '0']++;
        else uns++;

        s++;
    }

    int m = 0;
    
    while(*g != '\0') {
        m++;
        int c = tolower(*g);
        if(isalpha(c)){
            alpha[c - 'a'] = 0;
        } else if(isdigit(c)) {
            diz[c - '0'] = 0;
        } else if(*g == '_') {
            uns = 0;
        } else{
            return -1;
        }

        if(ok(alpha, diz, uns)) {
            return m;
        }

        g++;
    }

    return -1;
}

int main() {

    // long long int lcm = 1;
    // for(int i = 2 ; i < 50 ; i++) {
    //     lcm = (lcm * i ) / gcd(lcm, i);
    // }

    // printf("%lld\n", lcm);

    int n;
    char s[130], g[55];

    double sa = 0, sb = 0;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%s%s", s, g);

        int m = play(s, g);

        if(i & 1) {
            // a guesses
            if(m > 0) sa += (double)1 / m;
            else sb += (double)1 / 37;
        } else {
            // b guesses
            if(m > 0) sb += (double)1 / m;
            else sa += (double)1 / 37;
        }
    }

    // sa = sa / (double) lcm;
    // sb = sb / (double) lcm;

    printf("%.6lf %.6lf\n", sa, sb);

    return 0;
}