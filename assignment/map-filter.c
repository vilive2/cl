#include<stdlib.h>
#include<string.h>

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