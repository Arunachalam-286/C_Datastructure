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

// Function to find the index of a value in an array
int findIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive function to build the tree
struct TreeNode* buildTreeHelper(int* preorder, int* inorder, int inorderStart, int inorderEnd, int* preorderIndex) {
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // The current root is the next element in the preorder traversal
    int rootValue = preorder[*preorderIndex];
    (*preorderIndex)++;

    struct TreeNode* root = createTreeNode(rootValue);

    // If there are no more elements in this subtree
    if (inorderStart == inorderEnd) {
        return root;
    }

    // Find the index of the root in the inorder traversal
    int rootIndex = findIndex(inorder, inorderStart, inorderEnd, rootValue);

    // Recursively build the left and right subtrees
    root->left = buildTreeHelper(preorder, inorder, inorderStart, rootIndex - 1, preorderIndex);
    root->right = buildTreeHelper(preorder, inorder, rootIndex + 1, inorderEnd, preorderIndex);

    return root;
}

// Function to build the tree from preorder and inorder traversals
struct TreeNode* buildTree(int* preorder, int* inorder, int n) {
    int preorderIndex = 0;
    return buildTreeHelper(preorder, inorder, 0, n - 1, &preorderIndex);
}

// Function to print the tree in inorder (for verification)
void printInOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printInOrder(root->left);
    printf("%d ", root->val);
    printInOrder(root->right);
}

// Function to print the tree in preorder (for verification)
void printPreOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Main function to test the construction
int main() {
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    int n = sizeof(preorder) / sizeof(preorder[0]);

    struct TreeNode* root = buildTree(preorder, inorder, n);

    printf("Inorder Traversal of Constructed Tree: ");
    printInOrder(root);
    printf("\n");

    printf("Preorder Traversal of Constructed Tree: ");
    printPreOrder(root);
    printf("\n");

    return 0;
}
