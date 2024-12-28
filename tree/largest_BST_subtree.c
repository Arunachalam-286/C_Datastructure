#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure to store information about a subtree
struct Info {
    int size;         // Size of the subtree
    int min;          // Minimum value in the subtree
    int max;          // Maximum value in the subtree
    int largestBSTSize; // Size of the largest BST in the subtree
    int isBST;        // Boolean to indicate if the subtree is a BST
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find the largest BST subtree
struct Info largestBST(struct Node* root) {
    if (root == NULL) {
        // An empty tree is a BST
        return (struct Info){0, INT_MAX, INT_MIN, 0, 1};
    }

    // Recur for left and right subtrees
    struct Info leftInfo = largestBST(root->left);
    struct Info rightInfo = largestBST(root->right);

    struct Info currentInfo;

    // Calculate size of the current subtree
    currentInfo.size = 1 + leftInfo.size + rightInfo.size;

    // Check if the current subtree is a BST
    if (leftInfo.isBST && rightInfo.isBST &&
        root->data > leftInfo.max && root->data < rightInfo.min) {
        currentInfo.isBST = 1;
        currentInfo.min = (root->left != NULL) ? leftInfo.min : root->data;
        currentInfo.max = (root->right != NULL) ? rightInfo.max : root->data;

        // Update the largest BST size
        currentInfo.largestBSTSize = currentInfo.size;
    } else {
        currentInfo.isBST = 0;
        currentInfo.largestBSTSize = (leftInfo.largestBSTSize > rightInfo.largestBSTSize) ?
                                      leftInfo.largestBSTSize : rightInfo.largestBSTSize;
    }

    return currentInfo;
}

// Wrapper function to find the largest BST subtree
int findLargestBSTSubtree(struct Node* root) {
    return largestBST(root).largestBSTSize;
}

// Main function
int main() {
    struct Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(1);
    root->left->right = createNode(8);
    root->right->right = createNode(7);

    printf("Size of the largest BST subtree: %d\n", findLargestBSTSubtree(root));

    return 0;
}
