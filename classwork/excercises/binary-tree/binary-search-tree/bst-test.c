#include<stdio.h>
#include<stdlib.h>
#include "../binary-tree.h"
#include "bst.h"
#define f(i, n) for(int i = 0 ; i < n ; i++)

int main() {

    TREE tree;
    int n;
    if(init_tree(&tree)) {
        printf("Failed to init, required capacity : %d\n", MAX_NODES);
        exit(1);
    } else {
        printf("Tree initialized.\n");
    }
    
    printf("Num of nodes: ");
    scanf("%d", &n);

    printf("enter %d node key values: ", n);
    for(int i = 0 ; i < n ; i++) {
        int key;
        scanf("%d", &key);
        if(bst_insert(&tree, key)) {
            printf("Failed to insert, capacity : %ld, size : %ld\n", tree.capacity, tree.size);
            exit(1);
        }
    }

    // print_nodelist(&t);
    // print_tree(&t, t.root);
    
    // operations
    // INSERT 1 
    // DELETE 2
    // SEARCH 3
    // PRINT 4
    int key;
    
    while(1) {
        print_tree(&tree, tree.root);
        printf("\n\nquery 1(insert), 2(delete), 3(search), exit?");
        int query_type;
        scanf("%d", &query_type);
        // printf("Query %d BEGIN\n", qnum);
        switch(query_type) {
            case 1:
                // INSERT
                scanf("%d", &key);
                printf("\n=>INSERT %d\n", key);
                bst_insert(&tree, key);
                break;
            case 2:
                // DELETE
                scanf("%d", &key);
                printf("\n=>DELETE %d\n", key);
                bst_delete(&tree, key);
                break;
            case 3:
                // SEARCH
                scanf("%d", &key);
                if(bst_search(&tree, key) < 0)
                    printf("key not found\n");
                else
                    printf("found\n");
                break;
            // case 4:
            //     // PRINT
            //     inorder(&t, t.root);
            //     printf("\n");
            //     break;
            default:
                fprintf(stderr, "invalid operation type: %d\n", query_type);
                exit(0);
        }

        printf("query success!\n");
        print_nodelist(&tree);
        // print_tree(&t, t.root);
        // printf("Query %d END\n", qnum);
    }

    return 0;
}