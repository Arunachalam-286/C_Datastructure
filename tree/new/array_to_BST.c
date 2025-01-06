#include <stdio.h>
#include <stdlib.h>

// Define the structure of a BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to convert sorted array to a balanced BST
struct Node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }

    // Find the middle element
    int mid = (start + end) / 2;

    // Create the root node with the middle element
    struct Node* root = createNode(arr[mid]);

    // Recursively build the left and right subtrees
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

// Function to perform inorder traversal of the BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal of the BST
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Main function to demonstrate the conversion
int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Convert the sorted array to a balanced BST
    struct Node* root = sortedArrayToBST(arr, 0, n - 1);

    printf("Inorder Traversal of the Balanced BST: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal of the Balanced BST: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
