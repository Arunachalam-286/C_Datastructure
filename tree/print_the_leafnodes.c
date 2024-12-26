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

// Function to print all the leaf nodes recursively
void printLeafNodes(TreeNode* root) {
    if (root == NULL) return; // Base case: empty tree
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->val); // Print the leaf node
        return;
    }
    // Recursively traverse left and right subtrees
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Print all the leaf nodes
    printf("Leaf nodes of the binary tree: ");
    printLeafNodes(root);
    printf("\n");

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
