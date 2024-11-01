#include<stdio.h>
#include<stdlib.h>
#include "../binary-tree.h"
#include "bst.h"
#define f(i, n) for(int i = 0 ; i < n ; i++)

int main() {

    TREE t;
    int n;
    printf("Num of nodes: ");
    scanf("%d", &n);
    if(init_tree(&t, n)) {
        exit(1);
    }

    printf("enter %d node key values: ", n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &(t.nodelist[i].data));
    }

    t.num_nodes = t.capacity;

    bst_build(&t);
    // print_nodelist(&t);
    // print_tree(&t, t.root);
    
    // operations
    // INSERT 1 
    // DELETE 2
    // SEARCH 3
    // PRINT 4
    int q, key;
    // scanf("%d", &q);

    while(1) {
        print_tree(&t, t.root);
        printf("\n\nquery 1(insert), 2(delete), 3(search), exit?");
        int query_type;
        scanf("%d", &query_type);
        // printf("Query %d BEGIN\n", qnum);
        switch(query_type) {
            case 1:
                // INSERT
                scanf("%d", &key);
                printf("\n=>INSERT %d\n", key);
                bst_insert(&t, t.root, key);
                break;
            case 2:
                // DELETE
                scanf("%d", &key);
                printf("\n=>DELETE %d\n", key);
                bst_delete(&t, t.root, key);
                break;
            case 3:
                // SEARCH
                scanf("%d", &key);
                if(bst_search(&t, t.root, key) < 0)
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
        // print_tree(&t, t.root);
        // printf("Query %d END\n", qnum);
    }

    return 0;
}