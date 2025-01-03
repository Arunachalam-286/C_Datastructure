int main() {
    int maxChildren = 3; // Max number of children per node

    // Construct the N-ary tree
    struct Node* root = createNode(1, maxChildren);
    struct Node* child1 = createNode(2, maxChildren);
    struct Node* child2 = createNode(3, maxChildren);
    struct Node* child3 = createNode(4, maxChildren);

    addChild(root, child1);
    addChild(root, child2);
    addChild(root, child3);

    struct Node* child4 = createNode(5, maxChildren);
    struct Node* child5 = createNode(6, maxChildren);
    addChild(child1, child4);
    addChild(child1, child5);

    // Perform Traversals
    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    printf("Level Order Traversal: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
