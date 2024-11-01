
int main() {

    TREE t;
    read_tree(&t);
    print_tree(&t);

    printf("height: %d\n", height(&t, t.root));
    printf("leaves: %d\n", leaves(&t, t.root));
    printf("weight: %d\n", weight(&t, t.root));

    printf("preorder: ");
    preorder(&t, t.root);
    printf("\n");

    printf("inorder: ");
    inorder(&t, t.root);
    printf("\n");

    printf("postorder: ");
    postorder(&t, t.root);
    printf("\n");


    int target = 12;
    printf("pathsum of %d exist: %d\n", target, pathsum(&t, t.root, target));

    return 0;
}
