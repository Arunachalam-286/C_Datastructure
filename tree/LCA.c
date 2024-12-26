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

// Function to find the lowest common ancestor (LCA) of two nodes
struct TreeNode* findLCA(struct TreeNode* root, int n1, int n2) {
    if (root == NULL) {
        return NULL; // Base case: If the tree is empty
    }

    // If either n1 or n2 matches the current node, this is a potential LCA
    if (root->val == n1 || root->val == n2) {
        return root;
    }

    // Recur for left and right subtrees
    struct TreeNode* leftLCA = findLCA(root->left, n1, n2);
    struct TreeNode* rightLCA = findLCA(root->right, n1, n2);

    // If both subtrees return non-NULL, this node is the LCA
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }

    // Otherwise, return the non-NULL subtree
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    // Example usage
    struct TreeNode* root = createNode(3);
    root->left = createNode(5);
    root->right = createNode(1);
    root->left->left = createNode(6);
    root->left->right = createNode(2);
    root->right->left = createNode(0);
    root->right->right = createNode(8);
    root->left->right->left = createNode(7);
    root->left->right->right = createNode(4);

    int n1 = 5, n2 = 1;
    struct TreeNode* lca = findLCA(root, n1, n2);
    if (lca != NULL) {
        printf("LCA of %d and %d is: %d\n", n1, n2, lca->val);
    } else {
        printf("LCA does not exist for %d and %d\n", n1, n2);
    }

    // Free allocated memory (not shown for simplicity)
    return 0;
}
