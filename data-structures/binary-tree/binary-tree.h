#ifndef _BT_
#define _BT_

typedef struct {
    int data;
    int left, right, parent;
} TNODE;

typedef struct{
    size_t capacity, num_nodes; 
    int root, freelist;
    TNODE *nodelist;
} TREE;

int init_tree(TREE *t, size_t capacity);
int get_free_node(TREE *t);
void free_node(TREE *t, int node);
void read_tree(TREE *t);
void print_nodelist(TREE *t);
void inorder(TREE *t, int root);
void preorder(TREE *t, int root);
void postorder(TREE *t, int root);
void print_tree(TREE *t, int root);
int height(TREE *t, int root);

#endif