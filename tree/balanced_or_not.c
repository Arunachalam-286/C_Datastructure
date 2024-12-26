#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to calculate the height of a tree
int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // If any subtree is unbalanced, propagate -1 upward
    if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to check if the binary tree is balanced
bool isBalanced(struct TreeNode* root) {
    return height(root) != -1;
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
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->left->left->left = createNode(6);

    if (isBalanced(root)) {
        printf("The binary tree is balanced.\n");
    } else {
        printf("The binary tree is not balanced.\n");
    }

    // Free allocated memory (not shown for simplicity)
    return 0;
}
