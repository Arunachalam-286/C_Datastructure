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

// Helper function to perform the flattening
void flattenTreeHelper(struct TreeNode* root, struct TreeNode** prev) {
    if (root == NULL) {
        return;
    }

    // Recur for the right subtree
    flattenTreeHelper(root->right, prev);

    // Recur for the left subtree
    flattenTreeHelper(root->left, prev);

    // Modify the current node
    root->right = *prev;
    root->left = NULL;

    // Update the previous node
    *prev = root;
}

// Function to flatten the binary tree into a linked list
void flattenTree(struct TreeNode* root) {
    struct TreeNode* prev = NULL;
    flattenTreeHelper(root, &prev);
}

// Function to print the flattened tree as a linked list
void printFlattenedTree(struct TreeNode* root) {
    while (root != NULL) {
        printf("%d ", root->val);
        root = root->right;
    }
    printf("\n");
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(5);
    root->left->left = createTreeNode(3);
    root->left->right = createTreeNode(4);
    root->right->right = createTreeNode(6);

    printf("Flattening the binary tree...\n");
    flattenTree(root);

    printf("Flattened tree (as linked list):\n");
    printFlattenedTree(root);

    return 0;
}
