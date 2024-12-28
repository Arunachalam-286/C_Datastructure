#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Utility function to calculate the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Utility function to find the maximum path sum
int findMaxPathSum(struct Node* root, int* maxSum) {
    if (root == NULL)
        return 0;

    // Recur for left and right subtrees
    int leftSum = max(0, findMaxPathSum(root->left, maxSum));
    int rightSum = max(0, findMaxPathSum(root->right, maxSum));

    // Maximum path sum for the current node
    int currentMax = root->data + leftSum + rightSum;

    // Update the global maximum
    *maxSum = max(*maxSum, currentMax);

    // Return the maximum sum including the current node and one subtree
    return root->data + max(leftSum, rightSum);
}

// Function to calculate the maximum path sum in the binary tree
int maxPathSum(struct Node* root) {
    int maxSum = INT_MIN;
    findMaxPathSum(root, &maxSum);
    return maxSum;
}

// Main function
int main() {
    struct Node* root = createNode(10);
    root->left = createNode(2);
    root->right = createNode(10);
    root->left->left = createNode(20);
    root->left->right = createNode(1);
    root->right->right = createNode(-25);
    root->right->right->left = createNode(3);
    root->right->right->right = createNode(4);

    printf("Maximum Path Sum: %d\n", maxPathSum(root));

    return 0;
}
