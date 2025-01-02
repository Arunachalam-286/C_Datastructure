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
struct TreeNode* buildTreeHelper(int* inorder, int* postorder, int inorderStart, int inorderEnd, int* postorderIndex) {
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // The current root is the last element in the postorder traversal
    int rootValue = postorder[*postorderIndex];
    (*postorderIndex)--;

    struct TreeNode* root = createTreeNode(rootValue);

    // If there are no more elements in this subtree
    if (inorderStart == inorderEnd) {
        return root;
    }

    // Find the index of the root in the inorder traversal
    int rootIndex = findIndex(inorder, inorderStart, inorderEnd, rootValue);

    // Recursively build the right and left subtrees
    root->right = buildTreeHelper(inorder, postorder, rootIndex + 1, inorderEnd, postorderIndex);
    root->left = buildTreeHelper(inorder, postorder, inorderStart, rootIndex - 1, postorderIndex);

    return root;
}

// Function to build the tree from inorder and postorder traversals
struct TreeNode* buildTree(int* inorder, int* postorder, int n) {
    int postorderIndex = n - 1;
    return buildTreeHelper(inorder, postorder, 0, n - 1, &postorderIndex);
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

// Function to print the tree in postorder (for verification)
void printPostOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->val);
}

// Main function to test the construction
int main() {
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    struct TreeNode* root = buildTree(inorder, postorder, n);

    printf("Inorder Traversal of Constructed Tree: ");
    printInOrder(root);
    printf("\n");

    printf("Postorder Traversal of Constructed Tree: ");
    printPostOrder(root);
    printf("\n");

    return 0;
}
