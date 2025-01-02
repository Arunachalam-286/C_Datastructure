#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to check if two trees are identical
bool areIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    }

    if (root1 == NULL || root2 == NULL) {
        return false;
    }

    return (root1->val == root2->val &&
            areIdentical(root1->left, root2->left) &&
            areIdentical(root1->right, root2->right));
}

// Function to check if T is a subtree of S
bool isSubtree(struct TreeNode* S, struct TreeNode* T) {
    if (T == NULL) {
        return true; // An empty tree is always a subtree
    }

    if (S == NULL) {
        return false; // A non-empty tree cannot be a subtree of an empty tree
    }

    if (areIdentical(S, T)) {
        return true;
    }

    // Check the left and right subtrees of S
    return isSubtree(S->left, T) || isSubtree(S->right, T);
}

// Main function to test the implementation
int main() {
    // Create tree S
    struct TreeNode* S = createTreeNode(3);
    S->left = createTreeNode(4);
    S->right = createTreeNode(5);
    S->left->left = createTreeNode(1);
    S->left->right = createTreeNode(2);
    S->left->right->left = createTreeNode(0); // Added extra node

    // Create tree T
    struct TreeNode* T = createTreeNode(4);
    T->left = createTreeNode(1);
    T->right = createTreeNode(2);

    // Check if T is a subtree of S
    if (isSubtree(S, T)) {
        printf("Tree T is a subtree of Tree S.\n");
    } else {
        printf("Tree T is NOT a subtree of Tree S.\n");
    }

    return 0;
}
