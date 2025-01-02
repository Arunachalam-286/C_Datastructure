#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to print a path
void printPath(int* path, int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Recursive function to find paths with the given sum
void findPathsHelper(struct TreeNode* root, int targetSum, int* path, int pathLen, int currentSum) {
    if (root == NULL) {
        return;
    }

    // Add the current node to the path
    path[pathLen] = root->val;
    pathLen++;
    currentSum += root->val;

    // Check if the current path has the target sum and ends at a leaf
    if (root->left == NULL && root->right == NULL && currentSum == targetSum) {
        printPath(path, pathLen);
    }

    // Recur for left and right subtrees
    findPathsHelper(root->left, targetSum, path, pathLen, currentSum);
    findPathsHelper(root->right, targetSum, path, pathLen, currentSum);
}

// Function to find all paths with the given sum
void findPaths(struct TreeNode* root, int targetSum) {
    int path[1000]; // Array to store the current path (assuming max depth is 1000)
    findPathsHelper(root, targetSum, path, 0, 0);
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(5);
    root->left = createTreeNode(4);
    root->right = createTreeNode(8);
    root->left->left = createTreeNode(11);
    root->left->left->left = createTreeNode(7);
    root->left->left->right = createTreeNode(2);
    root->right->left = createTreeNode(13);
    root->right->right = createTreeNode(4);
    root->right->right->left = createTreeNode(5);
    root->right->right->right = createTreeNode(1);

    int targetSum = 22;

    printf("Paths with sum %d:\n", targetSum);
    findPaths(root, targetSum);

    return 0;
}
