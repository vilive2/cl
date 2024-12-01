#ifndef _AVL_
#define _AVL_

typedef struct {
    void *key;
    int left;
    int right; 
    int height;
    void *other;
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

int avl_init(TREE *tree, size_t key_size, size_t capacity, int (*comp)(const void *, const void *));
int avl_search(TREE *tree, const void *key);
int avl_insert(TREE *tree, const void *key);
int avl_delete(TREE *tree, const void *key);
int avl_keys(TREE *tree, void **keys);

#endif // _AVL_