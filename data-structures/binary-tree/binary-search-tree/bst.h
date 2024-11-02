#ifndef _BST_
#define _BST_

void bst_build(TREE *t);
int bst_search(TREE *t, int key);
void bst_insert(TREE *t, int key);
int bst_minimum(TREE *t, int root);
int bst_successor(TREE *t, int root);
void bst_delete(TREE *t, int root, int key);

#endif // _BST_