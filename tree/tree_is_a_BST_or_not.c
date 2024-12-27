#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure of a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Helper function to check if the binary tree is a BST
int isBSTUtil(struct Node* root, int min, int max) {
    // An empty tree is a BST
    if (root == NULL) {
        return 1;
    }

    // Check if the current node's value violates the BST property
    if (root->data <= min || root->data >= max) {
        return 0;
    }

    // Recursively check the left and right subtrees with updated ranges
    return isBSTUtil(root->left, min, root->data) &&
           isBSTUtil(root->right, root->data, max);
}

// Function to check if a binary tree is a BST
int isBST(struct Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Function to perform in-order traversal of the tree
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Main function to demonstrate checking if a tree is a BST
int main() {
    struct Node* root = createNode(50);
    root->left = createNode(30);
    root->right = createNode(70);
    root->left->left = createNode(20);
    root->left->right = createNode(40);
    root->right->left = createNode(60);
    root->right->right = createNode(80);

    printf("In-order traversal of the tree: ");
    inorderTraversal(root);
    printf("\n");

    if (isBST(root)) {
        printf("The tree is a Binary Search Tree.\n");
    } else {
        printf("The tree is NOT a Binary Search Tree.\n");
    }

    // Example of a non-BST
    struct Node* nonBST = createNode(50);
    nonBST->left = createNode(70); // Invalid BST property
    nonBST->right = createNode(30);

    printf("\nChecking another tree...\n");
    if (isBST(nonBST)) {
        printf("The tree is a Binary Search Tree.\n");
    } else {
        printf("The tree is NOT a Binary Search Tree.\n");
    }

    return 0;
}
