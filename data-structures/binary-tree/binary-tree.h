#ifndef _BT_
#define _BT_

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define HEIGHT(T, nodeindex) ( ((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height )
#define MAX_NODES 100

typedef int DATA;

typedef struct {
    DATA data;
    int left;
    int right; 
    int parent;
    int height;
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
int get_free_node(TREE *t);
void free_node(TREE *t, int node);

void read_tree(TREE *t);
void print_nodelist(TREE *t);
void print_tree(TREE *t, int root);

// TREE UTILITIES
int height(TREE *t, int root);


// TREE TRAVERSAL
void inorder(TREE *t, int root, int *dest, int *cur_index);
void preorder(TREE *t, int root, int *dest, int *cur_index);
void postorder(TREE *t, int root, int *dest, int *cur_index);


#endif