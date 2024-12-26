#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to calculate the diameter of the tree and the height simultaneously
int calculateDiameter(struct TreeNode* root, int* diameter) {
    if (root == NULL) {
        return 0;
    }

    // Calculate the height of the left and right subtrees
    int leftHeight = calculateDiameter(root->left, diameter);
    int rightHeight = calculateDiameter(root->right, diameter);

    // Update the diameter if the current path is longer
    int currentDiameter = leftHeight + rightHeight;
    if (currentDiameter > *diameter) {
        *diameter = currentDiameter;
    }

    // Return the height of the current node
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to find the diameter of the binary tree
int findDiameter(struct TreeNode* root) {
    int diameter = 0;
    calculateDiameter(root, &diameter);
    return diameter;
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
    root->right->right = createNode(6);

    int diameter = findDiameter(root);
    printf("The diameter of the binary tree is: %d\n", diameter);

    // Free allocated memory (not shown for simplicity)
    return 0;
}
