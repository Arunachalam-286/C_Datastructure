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

// Function to insert a node into the BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to find the kth smallest element using inorder traversal
void findKthSmallest(struct Node* root, int* k, int* result) {
    if (root == NULL || *k <= 0) {
        return;
    }

    // Traverse the left subtree
    findKthSmallest(root->left, k, result);

    // Visit the root
    (*k)--;
    if (*k == 0) {
        *result = root->data;
        return;
    }

    // Traverse the right subtree
    findKthSmallest(root->right, k, result);
}

// Function to find the kth largest element using reverse inorder traversal
void findKthLargest(struct Node* root, int* k, int* result) {
    if (root == NULL || *k <= 0) {
        return;
    }

    // Traverse the right subtree
    findKthLargest(root->right, k, result);

    // Visit the root
    (*k)--;
    if (*k == 0) {
        *result = root->data;
        return;
    }

    // Traverse the left subtree
    findKthLargest(root->left, k, result);
}

// Main function to demonstrate finding kth smallest and kth largest elements
int main() {
    struct Node* root = NULL;

    // Insert nodes into the BST
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    int k, result;

    // Find kth smallest element
    k = 3; // Change k as needed
    result = -1;
    findKthSmallest(root, &k, &result);
    if (result != -1) {
        printf("The %dth smallest element is %d\n", 3, result);
    } else {
        printf("The %dth smallest element does not exist.\n", 3);
    }

    // Find kth largest element
    k = 2; // Change k as needed
    result = -1;
    findKthLargest(root, &k, &result);
    if (result != -1) {
        printf("The %dth largest element is %d\n", 2, result);
    } else {
        printf("The %dth largest element does not exist.\n", 2);
    }

    return 0;
}
