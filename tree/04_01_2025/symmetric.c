#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to create a new node
struct Node* createNode(int val) {
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Function to insert values manually for symmetry
void insertManual() {
    root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(2);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right->left = createNode(4);
    root->right->right = createNode(3);
}

// Function to check if two trees are mirror images
int isMirror(struct Node *tree1, struct Node *tree2) {
    if (tree1 == NULL && tree2 == NULL)
        return 1; // Both are NULL, symmetric
    if (tree1 == NULL || tree2 == NULL)
        return 0; // One is NULL, not symmetric

    // Check data and recursive symmetry of subtrees
    return (tree1->data == tree2->data &&
            isMirror(tree1->left, tree2->right) &&
            isMirror(tree1->right, tree2->left));
}

// Function to check if the tree is symmetric
int isSymmetric(struct Node *node) {
    if (node == NULL)
        return 1; // Empty tree is symmetric
    return isMirror(node->left, node->right);
}

// Inorder traversal to display the tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    // Create a symmetric binary tree manually
    insertManual();

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Check if the binary tree is symmetric
    if (isSymmetric(root)) {
        printf("The tree is symmetric.\n");
    } else {
        printf("The tree is not symmetric.\n");
    }

    return 0;
}
