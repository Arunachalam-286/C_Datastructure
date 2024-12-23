#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to check if a binary tree is complete
bool isCompleteBinaryTree(TreeNode* root) {
    if (root == NULL) {
        return true; // An empty tree is complete
    }

    // Queue for level-order traversal
    TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root; // Enqueue root node
    bool foundNull = false;

    while (front < rear) {
        TreeNode* current = queue[front++]; // Dequeue a node

        if (current == NULL) {
            foundNull = true; // Mark the presence of a NULL node
        } else {
            if (foundNull) {
                // If a non-NULL node is found after a NULL node
                return false;
            }
            queue[rear++] = current->left;  // Enqueue left child
            queue[rear++] = current->right; // Enqueue right child
        }
    }

    return true;
}

// Main function to test the solution
int main() {
    // Create a sample binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    // Check if the tree is complete
    if (isCompleteBinaryTree(root)) {
        printf("The binary tree is a complete binary tree.\n");
    } else {
        printf("The binary tree is NOT a complete binary tree.\n");
    }

    return 0;
}
