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

// Function to check if two binary trees are identical recursively
int areIdentical(TreeNode* root1, TreeNode* root2) {
    // Base cases
    if (root1 == NULL && root2 == NULL) return 1; // Both trees are empty
    if (root1 == NULL || root2 == NULL) return 0; // One tree is empty

    // Check current nodes and recursively check left and right subtrees
    return (root1->val == root2->val) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

// Main function to test the implementation
int main() {
    // Create two sample binary trees
    TreeNode* root1 = createNode(1);
    root1->left = createNode(2);
    root1->right = createNode(3);
    root1->left->left = createNode(4);
    root1->left->right = createNode(5);

    TreeNode* root2 = createNode(1);
    root2->left = createNode(2);
    root2->right = createNode(3);
    root2->left->left = createNode(4);
    root2->left->right = createNode(5);

    // Check if the two trees are identical
    if (areIdentical(root1, root2)) {
        printf("The two binary trees are identical.\n");
    } else {
        printf("The two binary trees are not identical.\n");
    }

    // Free memory (optional for small programs)
    free(root1->left->left);
    free(root1->left->right);
    free(root1->left);
    free(root1->right);
    free(root1);
    free(root2->left->left);
    free(root2->left->right);
    free(root2->left);
    free(root2->right);
    free(root2);

    return 0;
}
