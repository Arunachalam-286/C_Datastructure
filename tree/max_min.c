#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition of a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the maximum value in a binary tree
int findMax(TreeNode* root) {
    if (root == NULL) return INT_MIN; // Sentinel value for empty tree
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    return (root->val > leftMax ? (root->val > rightMax ? root->val : rightMax) : (leftMax > rightMax ? leftMax : rightMax));
}

// Function to find the minimum value in a binary tree
int findMin(TreeNode* root) {
    if (root == NULL) return INT_MAX; // Sentinel value for empty tree
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    return (root->val < leftMin ? (root->val < rightMin ? root->val : rightMin) : (leftMin < rightMin ? leftMin : rightMin));
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // Find and print the maximum and minimum values
    printf("Maximum value in the binary tree: %d\n", findMax(root));
    printf("Minimum value in the binary tree: %d\n", findMin(root));

    // Free memory (optional for small programs)
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
