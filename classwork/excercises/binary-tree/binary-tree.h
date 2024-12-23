#ifndef _BT_
#define _BT_

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define HEIGHT(T, nodeindex) ( ((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height )

typedef void * DATA;

typedef struct {
    DATA data;
    int left;
    int right; 
    int parent;
    int height;
    void *other;
} TNODE;

typedef struct{
    size_t capacity;
    size_t size; 
    size_t key_size;
    int root;
    int freelist;
    TNODE *nodelist;
    int (*comp)(const void *, const void *);
} TREE;

// TREE MEMORY 
int init_tree(TREE *tree, size_t key_size, int (*comp)(const void *, const void *));
int get_free_node(TREE *t);
void free_node(TREE *t, int node);

void read_tree(TREE *t);
void print_nodelist(TREE *t);
void print_tree(TREE *t, int root);

// TREE UTILITIES
int height(TREE *t, int root);

// TREE TRAVERSAL
void inorder(TREE *t, int root, void **dest);

#endif