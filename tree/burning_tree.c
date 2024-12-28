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

// Utility function to find the target node and calculate burning times
int burnTree(struct Node* root, int target, int* maxTime, int* found) {
    if (root == NULL)
        return -1;

    // If target node is found
    if (root->data == target) {
        *found = 1;
        return 0;
    }

    // Recur for left and right subtrees
    int leftTime = burnTree(root->left, target, maxTime, found);
    int rightTime = burnTree(root->right, target, maxTime, found);

    // If target is found in left subtree
    if (*found && leftTime != -1) {
        *maxTime = *maxTime > leftTime + 1 ? *maxTime : leftTime + 1;
        return leftTime + 1;
    }

    // If target is found in right subtree
    if (*found && rightTime != -1) {
        *maxTime = *maxTime > rightTime + 1 ? *maxTime : rightTime + 1;
        return rightTime + 1;
    }

    return -1; // Target not found in current subtree
}

// Helper function to calculate the burning time for the entire tree
void calculateBurnTime(struct Node* root, int target, int* maxTime) {
    int found = 0;
    burnTree(root, target, maxTime, &found);
}

// Main function
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int target = 5;
    int maxTime = 0;

    calculateBurnTime(root, target, &maxTime);

    printf("Time taken to burn the entire tree: %d\n", maxTime);

    return 0;
}
