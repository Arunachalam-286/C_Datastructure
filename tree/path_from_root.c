#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Helper function to find the path from the root to the target node
bool findPath(struct TreeNode* root, int target, int path[], int* pathLen) {
    if (root == NULL) {
        return false;
    }

    // Add the current node to the path
    path[*pathLen] = root->val;
    (*pathLen)++;

    // Check if the current node is the target
    if (root->val == target) {
        return true;
    }

    // Recur for the left and right subtrees
    if (findPath(root->left, target, path, pathLen) ||
        findPath(root->right, target, path, pathLen)) {
        return true;
    }

    // If the target is not found, remove the current node from the path
    (*pathLen)--;
    return false;
}

// Function to print the path from the root to the target node
void printPathToNode(struct TreeNode* root, int target) {
    int path[100]; // Array to store the path (assuming at most 100 nodes in the tree)
    int pathLen = 0;

    if (findPath(root, target, path, &pathLen)) {
        printf("Path to node %d: ", target);
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Node %d not found in the tree.\n", target);
    }
}

int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int target = 5;
    printPathToNode(root, target);

    target = 8;
    printPathToNode(root, target);

    // Free allocated memory (not shown for simplicity)
    return 0;
}
