#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<assert.h>

#ifndef _BLOOM_
#define _BLOOM_

typedef struct {
    void *store;
    unsigned int m, k;
} BLOOM;

int bloom_init(BLOOM *bloom, unsigned int m, unsigned int k);
int bloom_insert(BLOOM *bloom, int x);

#endif // _BLOOM_

#ifndef _AVL_
#define _AVL_

typedef struct {
    void *key;
    int left;
    int right; 
    int height;
} TNODE;

typedef struct{
    TNODE *nodelist;
    size_t key_size;
    size_t size; 
    size_t capacity;
    int root;
    int freelist;
    int (*comp)(const void *, const void *);
} TREE;

int avl_init(TREE *tree, size_t key_size, int (*comp)(const void *, const void *));
int avl_search(TREE *tree, const void *key);
int avl_insert(TREE *tree, const void *key);
int avl_delete(TREE *tree, const void *key);
int avl_keys(TREE *tree, void *keys);
void avl_print_rotated(TREE *t, void (*printkey)(const void *), int maxwidth);
void avl_print_preorder(TREE *t, void (*printkey)(const void *));

#endif // _AVL_

int comp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void printkey(const void *el) {
    printf("%d ", *(int *)el);
}

unsigned int m, k, n, x;

int main() {
    scanf("%d%d%d", &m, &k, &n);

    BLOOM bloom;
    bloom_init(&bloom, m, k);

    TREE tree;
    avl_init(&tree, sizeof(int), comp);
    int bloom_error = 0;

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &x);
        if(avl_insert(&tree, &x)) 
            printf("AVL %d %d\n", i, x);
        else
            bloom_error++;

        if(bloom_insert(&bloom, x)) 
            printf("BLOOM %d %d\n", i, x);
        else
            bloom_error--;
    }

    printf("%d\n", bloom_error);
    avl_print_preorder(&tree, printkey);
    printf("\n");

    free(tree.nodelist[0].key);
    free(tree.nodelist);
    free(bloom.store);

    return 0;
}

/*************************************************************/
/*********************** BLOOM FILTER ************************/
/*************************************************************/

int bloom_init(BLOOM *bloom, unsigned int m, unsigned int k) {
    int size = (m + 7)/ 8;
    bloom->m = m;
    bloom->k = k;

    if(NULL == (bloom->store = malloc(size))) 
        return -1;
    
    memset(bloom->store, 0, size);

    return 0;
}

int bloom_insert(BLOOM *bloom, int x) {
    srand(x);
    int duplicate = 1;
    for(int i = 0 ; i < bloom->k ; i++) {
        int hi = rand() % bloom->m;
        int byte = hi / 8;
        int bit = hi % 8;

        char *c = bloom->store + byte;
        if(!((*c) & (1<<bit))) 
            duplicate = 0;

        *c = (*c) | (1<<bit);
    }

    return duplicate;
}

/*************************************************************/
/*********************** AVL *********************************/
/*************************************************************/

int avl_insert_(TREE *, int, int);
int avl_delete_(TREE *, int, const void *, int *);
extern void free_node(TREE *, int);
extern int get_free_node(TREE *);
extern void inorder(TREE *, int, void **);

int avl_init(TREE *tree, size_t key_size, int (*comp)(const void *, const void *)) {
    assert(tree != NULL);
    assert(key_size != 0);
    assert(comp != NULL);

    tree->key_size = key_size;
    tree->comp = comp;
    tree->capacity = 1;
    tree->size = 0;
    if(NULL == (tree->nodelist = (TNODE *)malloc(tree->capacity*sizeof(TNODE)))) {
        return -1;
    }

    if(NULL == (tree->nodelist[0].key = malloc(key_size))) {
        return -1;
    }

    tree->root = -1;
    tree->freelist = 0;

    tree->nodelist[0].right = -1;
    
    return 0;
}

int avl_search(TREE *tree, const void *key) {
    int cur = tree->root;
    while(cur != -1) {
        int r = tree->comp(tree->nodelist[cur].key, key);
        if( r == 0 ) 
            break;
        else if(r < 0) 
            cur = tree->nodelist[cur].right;
        else 
            cur = tree->nodelist[cur].left;
    }

    return cur;
}

int avl_insert(TREE *tree, const void *key) {
    if(avl_search(tree, key) != -1) 
        return 1;

    int key_index = get_free_node(tree);
    if(key_index<0) {
        return -1;
    }

    tree->nodelist[key_index].left = -1;
    tree->nodelist[key_index].right = -1;
    memcpy(tree->nodelist[key_index].key, key, tree->key_size);

    tree->nodelist[key_index].height = 0;
    tree->root = avl_insert_(tree, tree->root, key_index); 
    tree->size++;

    return 0;
}

int avl_delete(TREE *tree, const void *key) {
    int key_index;
    tree->root = avl_delete_(tree, tree->root, key, &key_index);

    if(key_index < 0)
        return -1;

    free_node(tree, key_index);
    tree->size--;

    return 0;
}

int avl_keys(TREE *tree, void *keys) {
    inorder(tree, tree->root, &keys);
    return 0;
}

// driver functions
extern int balance(TREE *tree, int root_index);
extern int successor(TREE *tree, int root_index);

int avl_insert_(TREE *tree, int root_index, int key_index) {
    if(root_index == -1) 
        return key_index;
    else if(tree->comp(tree->nodelist[root_index].key, tree->nodelist[key_index].key) < 0) {
        tree->nodelist[root_index].right = avl_insert_(tree, tree->nodelist[root_index].right, key_index);
    } else if(tree->comp(tree->nodelist[root_index].key, tree->nodelist[key_index].key) > 0) {
        tree->nodelist[root_index].left = avl_insert_(tree, tree->nodelist[root_index].left, key_index);
    }
    
    return balance(tree, root_index);
}

int avl_delete_(TREE *tree, int root_index, const void *key, int *key_index) {
    if(root_index == -1) {
        *key_index = -1;
        return -1;
    }

    int r = tree->comp(key, tree->nodelist[root_index].key);
    if( r < 0 ) {
        tree->nodelist[root_index].left = avl_delete_(tree, tree->nodelist[root_index].left, key, key_index);
    } else if( r > 0 ) {
        tree->nodelist[root_index].right = avl_delete_(tree, tree->nodelist[root_index].right, key, key_index);
    } else {
        *key_index = root_index;
        if(tree->nodelist[root_index].left != -1 &&
            tree->nodelist[root_index].right != -1) {

            int succ_index = successor(tree, root_index);
            assert(succ_index != -1);
            tree->nodelist[root_index].right = avl_delete_(tree, tree->nodelist[root_index].right, 
                                                    tree->nodelist[succ_index].key, &succ_index);
            
            tree->nodelist[succ_index].left = tree->nodelist[root_index].left;
            tree->nodelist[succ_index].right = tree->nodelist[root_index].right;
            root_index = succ_index;
        } else if(tree->nodelist[root_index].left != -1) {
            root_index = tree->nodelist[root_index].left;
        } else {
            root_index = tree->nodelist[root_index].right;
        }
    }

    return balance(tree, root_index);
}

#define HEIGHT(T, nodeindex) ( ((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height )
#define MAX(a,b) (((a)>(b))?(a):(b))

int rotate_LL(TREE *tree, int root_index) {
    int k2 = root_index;
    int k1 = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;
    int X = tree->nodelist[k1].left;
    int Y = tree->nodelist[k1].right;

    // rotate
    tree->nodelist[k2].left = Y;
    tree->nodelist[k1].right = k2;

    // update heights
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, Y), HEIGHT(tree, Z));
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, k2));

    return k1;
}

int rotate_RR(TREE *tree, int root_index) {
    int k1 = root_index;
    int X = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int Y = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;

    // rotate
    tree->nodelist[k1].right = Y;
    tree->nodelist[k2].left = k1;

    // update heights
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, Y));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, Z));

    return k2;
}

int rotate_LR(TREE *tree, int root_index) {
    tree->nodelist[root_index].left = rotate_RR(tree, tree->nodelist[root_index].left);
    return rotate_LL(tree, root_index);
}

int rotate_RL(TREE *tree, int root_index) {
    tree->nodelist[root_index].right = rotate_LL(tree, tree->nodelist[root_index].right);
    return rotate_RR(tree, root_index);
}

int balance(TREE *tree, int root_index) {
    if(root_index == -1) 
        return -1;

    int left = tree->nodelist[root_index].left;
    int right = tree->nodelist[root_index].right;

    if(HEIGHT(tree, left) - HEIGHT(tree, right) > 1) {
        // L
        if(HEIGHT(tree, tree->nodelist[left].left) >= HEIGHT(tree, tree->nodelist[left].right)) {
            // L
            return rotate_LL(tree, root_index);
        } else {
            // R
            return rotate_LR(tree, root_index);
        }
    } else if(HEIGHT(tree, right) - HEIGHT(tree, left) > 1) {
        // R
        if(HEIGHT(tree, tree->nodelist[right].left) >= HEIGHT(tree, tree->nodelist[right].right)) {
            // L
            return rotate_RL(tree, root_index);
        } else {
            // R
            return rotate_RR(tree, root_index);
        }
    }

    tree->nodelist[root_index].height = 1 + MAX(HEIGHT(tree, left), HEIGHT(tree, right));

    return root_index;
}

int successor(TREE *tree, int root) {
    if(root == -1)
        return -1;

    int par = tree->nodelist[root].right;
    int cur = par;

    while(cur != -1) {
        par = cur;
        cur = tree->nodelist[cur].left;
    }

    return par;
}

void inorder(TREE *tree, int root, void **dest) {
    if(root == -1) return;

    inorder(tree, tree->nodelist[root].left, dest);
    memcpy(*dest, tree->nodelist[root].key, tree->key_size);
    *dest = (*dest) + tree->key_size;
    inorder(tree, tree->nodelist[root].right, dest);
}



void avl_print_preorder(TREE *t, void (*printkey)(const void *)) {
    void preorder(int root) {
        if(root == -1) return;
        printkey(t->nodelist[root].key);
        preorder(t->nodelist[root].left);
        preorder(t->nodelist[root].right);
    }

    preorder(t->root);
}

void free_node(TREE *tree, int node) {
    if(tree->freelist == -1) {
        tree->nodelist[node].right = -1;
    } else {
        tree->nodelist[node].right = tree->freelist;
    }
    tree->freelist = node;
}

int resize(TREE *tree);

int get_free_node(TREE *tree) {
    if(tree->freelist == -1) {
        if(resize(tree))
            return -1;
    }

    int node = tree->freelist;
    tree->freelist = tree->nodelist[node].right;

    return node;
}

int resize(TREE *tree) {
    size_t new_cap = tree->capacity * 2;
    if(NULL == (tree->nodelist = (TNODE *)realloc(tree->nodelist, new_cap * sizeof(TNODE)))) {
        return -1;
    } 

    void *dataptr = tree->nodelist[0].key;
    if(NULL == (dataptr = realloc(dataptr, new_cap * tree->key_size))) {
        return -1;
    }
    for(int i = 0 ; i < new_cap ; i++) {
        tree->nodelist[i].key = dataptr;
        dataptr = dataptr + tree->key_size;
    }

    for(int i = tree->size ; i < new_cap - 1 ; i++) {
        tree->nodelist[i].right = i + 1;
    }
    tree->nodelist[new_cap - 1].right = -1;
    tree->freelist = tree->size;
    tree->capacity = new_cap;

    return 0;
}

int print_tree_(TREE *tree, int root, int line_num, int *line_end, char (*lines)[201]);
void print_tree(TREE *tree, int root) {
    int h = 0;
    if(root != -1)
        h = 2 * tree->nodelist[root].height;
    printf("\nPRINT TREE : %d\n", h);
    char lines[h+1][201];
    for(int i = 0 ; i < h+1 ; i++) lines[i][0] = '\0';
    int line_end = -1;
    print_tree_(tree, root, 0, &line_end, lines);

    for(int i = 0 ; i < h+1 ; i++) {
        printf("%s\n", lines[i]);
    }
}

void fillspace(char *c, int end_index) {
    int start_index = strlen(c);
    for(int i = start_index ; i < end_index ; i++)
        c[i] = ' ';
    c[end_index] = '\0';
}

int min(int a, int b) {
    return a>b?b:a;
}

int print_tree_(TREE *tree, int root, int line_num, int *line_end, char (*lines)[201]) {
    if(root == -1) {
        return -1;
    }

    int root_index, left_child_index, right_child_index;

    int line_start = strlen(&lines[line_num][0]);
    fillspace(&(lines[line_num+1][0]), min(200, line_start));
    
    left_child_index = print_tree_(tree, tree->nodelist[root].left, line_num + 2, line_end, lines);
    for(int i = line_start ; i <= (*line_end) && i < 200 ; i++) {
        lines[line_num][i] = ' ';
        if(i>=left_child_index && left_child_index != -1)
            lines[line_num][i] = '-';
        
        lines[line_num+1][i] = ' ';
        if(i == left_child_index)
            lines[line_num+1][i] = '|';
    }

    lines[line_num+1][min(200, ((*line_end)+1))] = '\0'; 

    root_index = (*line_end)+1;
    *line_end = (*line_end) + 1 + snprintf(&lines[line_num][(*line_end)+1], 200 - min(200, (*line_end)+1) + 1, "%d", *(int *)tree->nodelist[root].key);

    fillspace(&(lines[line_num+1][0]), min(200, *line_end));

    line_start = *line_end;
    
    right_child_index = print_tree_(tree, tree->nodelist[root].right, line_num + 2, line_end, lines);
    for(int i = line_start ; i <= (*line_end) && i < 200 ; i++) {
        lines[line_num][i] = ' ';
        if(i <= right_child_index) 
            lines[line_num][i] = '-';

        lines[line_num+1][i] = ' ';
        if(i == right_child_index)
            lines[line_num+1][i] = '|';
    }
    lines[line_num][min(200, (*line_end)+1)] = '\0';
    lines[line_num+1][min(200, (*line_end)+1)] = '\0';

    return root_index;
}

void print_rotated_tree_(TREE *t, int root, int spaces, void (*printkey)(const void *), int maxwidth) {
    if(root == -1 || spaces > maxwidth) return;
    print_rotated_tree_(t, t->nodelist[root].right, spaces + 4, printkey, maxwidth);
    printf("%*s", spaces, "");
    printkey(t->nodelist[root].key);
    printf("\n");
    print_rotated_tree_(t, t->nodelist[root].left, spaces + 4, printkey, maxwidth);
}

void avl_print_rotated(TREE *t, void (*printkey)(const void *), int maxwidth) {
    print_rotated_tree_(t, t->root, 0, printkey, maxwidth);
}
