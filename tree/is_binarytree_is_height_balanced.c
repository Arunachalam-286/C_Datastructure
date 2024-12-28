#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Helper function to check height-balance and calculate height
int checkBalance(struct Node* root, bool* isBalanced) {
    if (root == NULL)
        return 0;

    // Recursively check left and right subtrees
    int leftHeight = checkBalance(root->left, isBalanced);
    int rightHeight = checkBalance(root->right, isBalanced);

    // If the difference in heights is more than 1, mark as unbalanced
    if (abs(leftHeight - rightHeight) > 1)
        *isBalanced = false;

    // Return the height of the current subtree
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to determine if the tree is height-balanced
bool isHeightBalanced(struct Node* root) {
    bool isBalanced = true;
    checkBalance(root, &isBalanced);
    return isBalanced;
}

// Main function
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->left->left->left = createNode(8);

    if (isHeightBalanced(root))
        printf("The tree is height-balanced.\n");
    else
        printf("The tree is not height-balanced.\n");

    return 0;
}
