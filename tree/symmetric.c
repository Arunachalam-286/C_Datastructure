#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to check if two subtrees are mirrors of each other
bool isMirror(struct TreeNode* left, struct TreeNode* right) {
    // Both subtrees are empty
    if (left == NULL && right == NULL) {
        return true;
    }

    // One of the subtrees is empty
    if (left == NULL || right == NULL) {
        return false;
    }

    // Check if the current nodes are equal and the left subtree of one
    // is the mirror of the right subtree of the other
    return (left->val == right->val) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}

// Function to check if the tree is symmetric
bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) {
        return true; // An empty tree is symmetric
    }
    return isMirror(root->left, root->right);
}

// Utility function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(2);
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    root->right->left = createNode(4);
    root->right->right = createNode(3);

    if (isSymmetric(root)) {
        printf("The binary tree is symmetric.\n");
    } else {
        printf("The binary tree is not symmetric.\n");
    }

    // Free allocated memory (not shown for simplicity)
    return 0;
}
