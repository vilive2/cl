#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

char lines[5][100];


void fill_char(char *str, char c, int i) {
    if(i<0) return;
    str[i+1] = '\0';
    while(i>=0 && str[i] != '\0') str[i--] = c;
    str[i] = c;
}

int print_tree_(TREE *t, int root, int d) {
    if(root == -1) return;

    TNODE node = t->nodelist[root];

    int l = strlen(lines[d]);

    // for leaf node
    if(node.left == -1 && node.right == -1) {
        sprintf(lines[d]+l, "%d\0", node.d);
        return l;
    }

    // left subtree print
    if(node.left != -1) {
        int left_child_loc = print_tree_(t, t->nodelist[root].left, d+2);
        // fill required chars
        fill_char(&lines[d+1], ' ', left_child_loc);
        fill_char(&lines[d+1], '|', left_child_loc);

        int len2 = strlen(lines[d+2]);
        fill_char(&lines[d+1], ' ', len2);
        fill_char(&lines[d], ' ', left_child_loc-1);
        fill_char(&lines[d], '-', len2);
        l = len2+1;
        for(int i = d+1 ; i < 5 ; i++) {
            fill_char(&lines[i], ' ', len2);
        }
    }


    // root
    int root_loc = l;
    sprintf(&lines[d][l], "%d\0", node.d);
    l = strlen(&lines[d]);
    for(int i = d+1; i < 5 ; i++) {
        fill_char(&lines[i], ' ', l);
    }

    // right subtree print
    if(node.right != -1) {
        int right_child_loc = print_tree_(t, t->nodelist[root].right, d+2);

        fill_char(&lines[d+1], ' ', right_child_loc);
        lines[d+1][right_child_loc] = '|';
        lines[d+1][right_child_loc+1] = '\0';
        fill_char(&lines[d], '-', right_child_loc);
    }

    printf("%s\n", lines[d]);
    return root_loc;
}

int main() {

    TREE t;
    read_tree(&t);
    print_tree(&t);

    for(int i = 0 ; i < 5 ; i++) {
        lines[i][0] = '\0';
        for(int j = 1 ; j < 100 ; j++) lines[i][j] = 'c';
    }
    print_tree_(&t, t.root, 0);


    for(int i = 0 ; i < 5 ; i++) {
        printf("%s\n", lines[i]);
    }

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