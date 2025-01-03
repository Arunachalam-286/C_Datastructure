#include <stdio.h>
#include <stdlib.h>

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

// Function to dynamically create a binary tree
TreeNode* createTree() {
    int val;
    printf("Enter node value (-1 for NULL): ");
    scanf("%d", &val);

    if (val == -1) {
        return NULL; // NULL indicates no node
    }

    TreeNode* root = createNode(val);
    printf("Entering left child of %d:\n", val);
    root->left = createTree(); // Recursively create the left subtree
    printf("Entering right child of %d:\n", val);
    root->right = createTree(); // Recursively create the right subtree

    return root;
}

// Function to calculate the height of the tree recursively
int findHeight(TreeNode* root) {
    if (root == NULL) return -1; // Return -1 for an empty tree (height in terms of edges)
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Main function to test the implementation
int main() {
    printf("Create your binary tree:\n");
    TreeNode* root = createTree();

    // Find and print the height of the binary tree
    int height = findHeight(root);
    printf("Height of the binary tree: %d\n", height);

    // Free memory (optional for small programs, but good practice)
    free(root);

    return 0;
}
