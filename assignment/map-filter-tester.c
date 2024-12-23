#include "common.h"

void *map(
    void *L, 
    unsigned int N,
    size_t domain_elt_size, 
    size_t range_elt_size,
    void (*f)(void *input, void *output)
) {
    void *R = malloc(N * range_elt_size);
    if(R == NULL) return NULL;

    for(int i = 0 ; i < N ; i++) {
        f(L + i * domain_elt_size, R + i * range_elt_size);
    }

    return R;
}

int filter(
    void *L, 
    unsigned int N, 
    size_t domain_elt_size,
    int (*g)(void *input)
) {

    void *aux = malloc(N * domain_elt_size);
    if(aux == NULL) return -1;

    int true_count = 0, false_count = 0;

    for(int i = 0 ; i < N ; i++) {
        if(g(L + i * domain_elt_size)) {
            memmove(
                L + true_count * domain_elt_size, 
                L + i * domain_elt_size, 
                domain_elt_size
            );
            true_count++;
        } else {
            memcpy(
                aux + false_count * domain_elt_size,
                L + i * domain_elt_size,
                domain_elt_size
            );
            false_count++;
        }
    }

    memcpy(
        L + true_count * domain_elt_size,
        aux,
        false_count * domain_elt_size
    );

    free(aux);

    return true_count;
}
// #include "map-filter-functions.c"
#include "CS2436_map-filter-functions.c"

int main(int ac, char *av[])
{
    char inbuf_char[] = "This is a test string, containing various characters\n",
        *inbuf_strings[] = {
            "You should upload a C file",
            "(say map-filter.c) containing",
            "\n\t\byour implementation of \"map-filter.c\"",
        },
        *out1;
    int inbuf_int[] = { 12394, 982763, 3765, 8761, 38971, 802948 }, i, *out2;
    int n;
    float *out3;

    n = strlen(inbuf_char)+1;
    out1 = map(inbuf_char, n, sizeof(char), sizeof(char), map1);
    for (i = 0; i < n; i++)
        printf("%d ", out1[i]);
    putchar('\n');

    n = sizeof(inbuf_strings)/sizeof(char *);
    out2 = map(inbuf_strings, n, sizeof(char *), sizeof(int), map2);
    for (i = 0; i < n; i++)
        printf("%d ", out2[i]);
    putchar('\n');

    n = sizeof(inbuf_int) / sizeof(int);
    out3 = map(inbuf_int, n, sizeof(int), sizeof(float), map3);
    for (i = 0; i < n; i++)
        printf("%f ", out3[i]);
    putchar('\n');

    int N = sizeof(inbuf_int) / sizeof(int);
    n = filter(inbuf_int, N, sizeof(int), filter1);
    for (i = 0; i < N; i++)
        printf("%d ", inbuf_int[i]);
    printf("%d\n", n);

    N = strlen(inbuf_char)+1;
    n = filter(inbuf_char, N, sizeof(char), filter2);
    for (i = 0; i < N; i++)
        printf("%c ", inbuf_char[i]);
    printf("%d\n", n);

    free(out1); free(out2); free(out3);
    return 0;
}
