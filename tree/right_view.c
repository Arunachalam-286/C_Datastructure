#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Utility function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Helper function to print the right view of the tree
void rightViewUtil(struct TreeNode* root, int level, int* maxLevel) {
    if (root == NULL) {
        return;
    }

    // If this is the first node of its level
    if (*maxLevel < level) {
        printf("%d ", root->val);
        *maxLevel = level;
    }

    // Recur for the right and left subtrees
    rightViewUtil(root->right, level + 1, maxLevel);
    rightViewUtil(root->left, level + 1, maxLevel);
}

// Function to print the right view of the binary tree
void printRightView(struct TreeNode* root) {
    int maxLevel = 0; // Tracks the maximum level visited
    rightViewUtil(root, 1, &maxLevel);
}

int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);
    root->left->right->left = createNode(7);

    printf("Right view of the binary tree: ");
    printRightView(root);
    printf("\n");

    // Free allocated memory (not shown for simplicity)
    return 0;
}
