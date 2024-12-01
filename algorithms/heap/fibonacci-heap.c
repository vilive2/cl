#include<stdio.h>
#define FALSE 0
#define TRUE 1

typedef struct node{
    int key;
    int degree;
    struct node *p;
    struct node *child;
    int mark;
    struct node *left, *right;
} FIB_HEAP_NODE;

typedef struct{
    FIB_HEAP_NODE *min;
    int n;
} FIB_HEAP;

void create_root_list(FIB_HEAP_NODE *x) {
    x->left=x;
    x->right=x;
}

void insert_into_root_list(FIB_HEAP *H, FIB_HEAP_NODE *x) {
    FIB_HEAP_NODE *min_right = H->min->right;
    H->min->right = x;
    x->left = H->min;
    x->right = min_right;
    min_right->left = x;
    x->p = NULL;
}

void fib_heap_insert(FIB_HEAP *H, FIB_HEAP_NODE *x) {
    x->degree = 0;
    x->child = NULL;
    x->mark = FALSE;

    if(H->min == NULL) {
        create_root_list(x);
        H->min = x;
    } else {
        insert_into_root_list(H, x);
        if(x->key < H->min->key) {
            H->min = x;
        }
    }

    H->n += 1;
}

FIB_HEAP *make_fib_heap() {
    FIB_HEAP *H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    if(H == NULL) {
        ferror("unable to allocate memory");
        exit(0);
    }

    H->min = NULL;
    H->n = 0;
    return H;
}

void merge_root_list(FIB_HEAP *H1, FIB_HEAP *H2) {
    if(H1 == NULL || H2 == NULL) return;

    FIB_HEAP_NODE *h1min_right = H1->min->right;
    FIB_HEAP_NODE *h2min_left = H2->min->left;

    H1->min->right = H2->min;
    H2->min->left = H1->min;

    h1min_right->left = h2min_left;
    h2min_left->right = h1min_right;
}

FIB_HEAP *fib_heap_union(FIB_HEAP *H1, FIB_HEAP *H2) {
    FIB_HEAP *H = make_fib_heap();
    H->min = H1.min;

    if(H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key)) {
        H->min = H2->min;
    }

    H->n = H1->n + H2->n;

    free(H1);
    free(H2);

    return H;
}

void remove_from_root_list(FIB_HEAP *H, FIB_HEAP_NODE *z) {
    z->left->right = z->right;
    z-right->left = z->left;
}

void make_child(FIB_HEAP_NODE *y, FIB_HEAP_NODE *x) {
    FIB_HEAP_NODE *xchild_right = x->child->right;

    y->p = x;
    x->d += 1;
    
    x->child->right = y;
    y->left = x->child;
    y->right = xchild_right;
    xchild_right->left = y;
}

void fib_heap_link(FIB_HEAP *H, FIB_HEAP_NODE *y, FIB_HEAP_NODE *x) {
    remove_from_root_list(H, y);
    make_child(y, x);
    y->mark = FALSE;
}

void consolidate(FIB_HEAP *H) {
    FIB_HEAP_NODE *A[D(H->n)];
    for(int i = 0 ; i < D(H->n); i++) \
        A[i] = NULL;
    
    FIB_HEAP_NODE *x = H->min, *y, *tmp, *next;
    do{
        int d = x->degree;
        next = x->right;

        while(A[d] != NULL) {
            y = A[d];
            if(x->key > y->key) {
                tmp = x;
                x = y;
                y = tmp;
            }
            fib_heap_link(H, y, x);
            A[d] = NULL;
            d += 1;
        }

        A[d] = x;
        x = next;
    }while(x != H->min);

    H->min = NULL;

    for(int i=0; i<D(H->n); i++) {
        if(A[i] != NULL) {
            if(H->min == NULL) {
                create_root_list(A[i]);
                H->min = A[i];
            } else {
                insert_into_root_list(H, A[i]);
                if(A[i]->key < H->min->key) {
                    H->min = A[i];
                }
            }
        }
    }
}

FIB_HEAP_NODE *fib_heap_extract_min(FIB_HEAP *H) {
    FIB_HEAP_NODE *z = H->min;

    if(z != NULL) {
        FIB_HEAP_NODE *cur_child = z->child, *next_child;
        for(int i=0; i<z->degree; i++) {
            next_child = cur_child->right;
            insert_into_root_list(H, cur_child);
            cur_child = next_child;
        }

        remove_from_root_list(H, z);
        if(z == z->right) {
            H->min = NULL;
        } else {
            H->min = z->right;
            consolidate(H);
        }

        H->n -= 1;
    }

    return z;
}

void fib_heap_decrease_key(FIB_HEAP *H, FIB_HEAP_NODE *x, int k) {
    if(k > x->key) {
        ferror("new key is greater than current key");
        return;
    }

    x->key = k;
    FIB_HEAP_NODE *y = x->p;
    if(y != NULL && x->key < y->key) {
        cut(H, x, y);
        cascading_cut(H, y);
    }

    if(x->key < H->min->key) {
        H->min = x;
    }
}

void cut(FIB_HEAP *H, FIB_HEAP_NODE *x, FIB_HEAP_NODE *y) {
    
}

int main() {

    return 0;
}