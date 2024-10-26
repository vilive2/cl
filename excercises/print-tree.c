#include<stdio.h>
#include<stdlib.h>

typedef struct tnode {
    int d;
    int left, right, parent;
} TNODE;

typedef struct{
    int capacity, num_nodes, root, free;
    TNODE *nodelist;
} TREE;

int init_tree(TREE *t, int capacity);
void read_tree(TREE *t);
void print_tree(TREE *t);

/*
print like this
  ----A----
  |       |
--B--     C--
|   |       |
D   E       F
*/

void print_tree_(TREE *t, int root) {
    if(root == -1) return;
    printf("%d\n", t->nodelist[root].d);
    print_tree_(t, t->nodelist[root].left);
    print_tree_(t, t->nodelist[root].right);
}

int main() {

    TREE t;
    read_tree(&t);
    print_tree(&t);
    print_tree_(&t, t.root);

    return 0;
}

int init_tree(TREE *t, int capacity) {
    t->capacity = capacity;
    t->num_nodes = 0;
    t->root = -1;
    t->nodelist = (TNODE *)malloc(capacity*sizeof(TNODE));
    if(t->nodelist == NULL) return -1;

    return 0;
}

void read_tree(TREE *t) {
    int num_nodes;
    scanf("%d", &num_nodes);
    if(init_tree(t, num_nodes) == -1) {
        fprintf(stderr, "out of memory");
        exit(0);
    }
    t->num_nodes = num_nodes;

    int i;
    TNODE *node;
    for(node = t->nodelist, i = 0; i < num_nodes; node++, i++){
        scanf("%d%d%d", &(node->d), &(node->left), &(node->right));
        if(node->left != -1) t->nodelist[node->left].parent = i;
        if(node->right != -1) t->nodelist[node->right].parent = i;
    }
    t->root=0;
}

void print_tree(TREE *t) {
    printf("Tree:\nnum_of_nodes: %d\n", t->num_nodes);
    printf("index data left right parent\n");
    int i;
    TNODE *node;
    for(node = t->nodelist, i = 0; i < t->num_nodes; node++, i++)
        printf("%5d %4d %4d %5d %6d\n", i, (node->d), (node->left), (node->right), (node->parent));
}