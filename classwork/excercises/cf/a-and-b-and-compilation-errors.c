#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define N 100001
#define f(i, n) for(int i = 0 ; i < n ; i++)

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define HEIGHT(T, nodeindex) ( ((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height )
#define MAX_NODES 100001

typedef int DATA;

typedef struct {
    DATA data;
    int left;
    int right; 
    int parent;
    int height;
    int count;
} TNODE;

typedef struct{
    size_t capacity;
    size_t size; 
    int root;
    int freelist;
    TNODE *nodelist;
} TREE;

// TREE MEMORY 
int init_tree(TREE *t);
void print_nodelist(TREE *t);
int get_free_node(TREE *t);
void free_node(TREE *t, int node);
int bst_insert(TREE *t, int key);
int bst_delete(TREE *t, int key);

int a[N];
int b[N];
int c[N];
int n, fix1, fix2;

int main() {

    scanf("%d", &n);
    
    TREE tree;
    init_tree(&tree);

    // print_nodelist(&tree);

    f(i, n) scanf("%d", &a[i]);
    
    f(i, n) bst_insert(&tree, a[i]);

    // print_nodelist(&tree);

    f(i, n-1) scanf("%d", &b[i]);

    f(i, n-1) bst_delete(&tree, b[i]);

    // print_nodelist(&tree);

    fix1 = tree.nodelist[tree.root].data;

    bst_delete(&tree, fix1);

    // print_nodelist(&tree);

    f(i, n-1) bst_insert(&tree, b[i]);

    // print_nodelist(&tree);

    f(i, n-2) scanf("%d", &c[i]);

    f(i, n-2) bst_delete(&tree, c[i]);

    // print_nodelist(&tree);

    fix2 = tree.nodelist[tree.root].data;

    printf("%d\n%d\n", fix1, fix2);

    return 0;
}

int init_tree(TREE *tree) {
    assert(tree != NULL);
    tree->capacity = MAX_NODES;
    tree->size = 0;
    if(NULL == (tree->nodelist = (TNODE *)malloc(tree->capacity*sizeof(TNODE)))) {
        return -1;
    }

    tree->root = -1;
    tree->freelist = 0;

    int i;
    for(i = 1 ; i < tree->capacity ; i++)
        tree->nodelist[i-1].right = i;

    tree->nodelist[i-1].right = -1;
    
    return 0;
}

void print_nodelist(TREE *tree) {
    printf("Tree:\nnum_of_nodes: %ld, root : %d\n", tree->size, tree->root);
    printf("index data left right parent height\n");
    int i;
    TNODE *node;
    for(node = tree->nodelist, i = 0; i < tree->size; node++, i++)
        printf("%5d %4d %4d %5d %6d %6d\n", i, (node->data), (node->left), (node->right), (node->parent), (node->height));
}

void free_node(TREE *tree, int node) {
    if(tree->freelist == -1) {
        tree->nodelist[node].right = -1;
    } else {
        tree->nodelist[node].right = tree->freelist;
    }
    tree->freelist = node;
}

int get_free_node(TREE *tree) {
    if(tree->freelist == -1)
        return -1;

    int node = tree->freelist;
    tree->freelist = tree->nodelist[node].right;

    return node;
}

int bst_successor(TREE *tree, int root) {
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

int bst_search(TREE *tree, DATA key) {
    int cur = tree->root;
    while(cur != -1) {
        if(tree->nodelist[cur].data == key) 
            break;
        else if(tree->nodelist[cur].data < key) 
            cur = tree->nodelist[cur].right;
        else 
            cur = tree->nodelist[cur].left;
    }

    return cur;
}

void bst_insert_(TREE *tree, int key_index);
int bst_delete_(TREE *tree, DATA key);

int bst_insert(TREE *tree, DATA key) {

    int key_index = bst_search(tree, key);

    if(key_index != -1) {
        tree->nodelist[key_index].count++;
        return 0;
    }

    key_index = get_free_node(tree);
    if(key_index<0) {
        return -1;
    }


    tree->nodelist[key_index].left = -1;
    tree->nodelist[key_index].right = -1;
    tree->nodelist[key_index].data = key;
    tree->nodelist[key_index].count = 1;

    bst_insert_(tree, key_index);
    tree->size++;

    return 0;
}

int bst_delete(TREE *tree, DATA key) {
    
    int key_index = bst_search(tree, key);

    if(key_index != -1) {
        tree->nodelist[key_index].count--;
        if(tree->nodelist[key_index].count)
            return 0;
    } else 
        return -1;

    key_index = bst_delete_(tree, key);

    if(key_index < 0)
        return -1;

    free_node(tree, key_index);
    tree->size--;

    return 0;
}

int bst_avl_insert_(TREE *tree, int root_index, int key_index);
int bst_avl_delete_(TREE *tree, int root_index, int key, int *key_index);

void bst_insert_(TREE *tree, int key_index) {
    tree->nodelist[key_index].height = 0;
    tree->root = bst_avl_insert_(tree, tree->root, key_index); 
}

int bst_delete_(TREE *tree, DATA key) {
    int key_index;

    tree->root = bst_avl_delete_(tree, tree->root, key, &key_index);

    return key_index;
}

int balance(TREE *tree, int root_index);

int bst_avl_insert_(TREE *tree, int root_index, int key_index) {
    if(root_index == -1) 
        return key_index;
    else if(tree->nodelist[root_index].data < tree->nodelist[key_index].data) {
        tree->nodelist[root_index].right = bst_avl_insert_(tree, tree->nodelist[root_index].right, key_index);
    } else if(tree->nodelist[root_index].data > tree->nodelist[key_index].data) {
        tree->nodelist[root_index].left = bst_avl_insert_(tree, tree->nodelist[root_index].left, key_index);
    }
    
    return balance(tree, root_index);
}

int bst_avl_delete_(TREE *tree, int root_index, int key, int *key_index) {
    if(root_index == -1) {
        *key_index = -1;
        return -1;
    }

    if( key < tree->nodelist[root_index].data ) {
        tree->nodelist[root_index].left = bst_avl_delete_(tree, tree->nodelist[root_index].left, key, key_index);
    } else if(key > tree->nodelist[root_index].data) {
        tree->nodelist[root_index].right = bst_avl_delete_(tree, tree->nodelist[root_index].right, key, key_index);
    } else {
        *key_index = root_index;
        if(tree->nodelist[root_index].left != -1 &&
            tree->nodelist[root_index].right != -1) {

            int succ_index = bst_successor(tree, root_index);
            assert(succ_index != -1);
            tree->nodelist[root_index].right = bst_avl_delete_(tree, tree->nodelist[root_index].right, 
                                                    tree->nodelist[succ_index].data, &succ_index);
            
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