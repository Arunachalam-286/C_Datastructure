#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to convert the binary tree to its mirror image
void mirrorTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Swap the left and right children
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively apply the same to the left and right subtrees
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Utility function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform an in-order traversal of the tree
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
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

    printf("Original tree (in-order traversal): ");
    inorderTraversal(root);
    printf("\n");

    mirrorTree(root);

    printf("Mirrored tree (in-order traversal): ");
    inorderTraversal(root);
    printf("\n");

    // Free allocated memory (not shown for simplicity)
    return 0;
}
