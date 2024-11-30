#ifndef _AVL_
#define _AVL_

typedef struct {
    void *data;
    int left;
    int right; 
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

int avl_init(TREE *tree, size_t key_size, int (*comp)(const void *, const void *));
int avl_search(TREE *tree, const void *key);
int avl_insert(TREE *tree, const void *key);
int avl_delete(TREE *tree, const void *key);
int avl_keys(TREE *tree, void **keys);

#endif // _AVL_