#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to print the left boundary excluding leaf nodes
void printLeftBoundary(struct TreeNode* root) {
    struct TreeNode* current = root;
    while (current) {
        if (current->left || current->right) {
            printf("%d ", current->val);
        }
        if (current->left) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
}

// Function to print all leaf nodes
void printLeafNodes(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->val);
        return;
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Function to print the right boundary excluding leaf nodes, in reverse order
void printRightBoundary(struct TreeNode* root) {
    struct TreeNode* current = root;
    int stack[100]; // Stack to store nodes for reverse order printing
    int top = -1;

    while (current) {
        if (current->left || current->right) {
            stack[++top] = current->val;
        }
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    // Print the stack in reverse order
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
}

// Function to print the boundary nodes of the binary tree
void printBoundary(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Print the root node
    printf("%d ", root->val);

    // Print the left boundary excluding leaf nodes
    if (root->left) {
        printLeftBoundary(root->left);
    }

    // Print all the leaf nodes
    printLeafNodes(root);

    // Print the right boundary excluding leaf nodes
    if (root->right) {
        printRightBoundary(root->right);
    }
}

// Utility function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
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
    root->left->right->left = createNode(8);
    root->left->right->right = createNode(9);

    printf("Boundary nodes of the binary tree: ");
    printBoundary(root);
    printf("\n");

    // Free allocated memory (not shown for simplicity)
    return 0;
}
