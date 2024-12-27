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

// Global variables for tracking mode(s)
int maxFrequency = 0;      // Max frequency observed so far
int currentFrequency = 0;  // Frequency of the current value
int currentValue;          // Current value being processed

// Function to find the mode(s) during inorder traversal
void findModes(struct Node* root, int* modes, int* modeCount) {
    if (root == NULL) {
        return;
    }

    // Recur for the left subtree
    findModes(root->left, modes, modeCount);

    // Process the current node
    if (root->data == currentValue) {
        currentFrequency++;
    } else {
        currentValue = root->data;
        currentFrequency = 1;
    }

    // Update the mode(s)
    if (currentFrequency > maxFrequency) {
        maxFrequency = currentFrequency;
        *modeCount = 1;
        modes[0] = currentValue;  // Reset and store the new mode
    } else if (currentFrequency == maxFrequency) {
        modes[*modeCount] = currentValue;  // Add the new mode
        (*modeCount)++;
    }

    // Recur for the right subtree
    findModes(root->right, modes, modeCount);
}

// Wrapper function to find and print the mode(s)
void printModes(struct Node* root) {
    int modes[100];  // Array to store the mode(s)
    int modeCount = 0; // Number of modes

    // Initialize the currentValue to a dummy value
    currentValue = -1;

    // Perform inorder traversal to find the mode(s)
    findModes(root, modes, &modeCount);

    // Print the mode(s)
    printf("Mode(s) in the BST: ");
    for (int i = 0; i < modeCount; i++) {
        printf("%d ", modes[i]);
    }
    printf("\n");
    printf("Max frequency: %d\n", maxFrequency);
}

// Main function to demonstrate finding the mode(s)
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
    root = insertNode(root, 60); // Duplicate to test mode
    root = insertNode(root, 70); // Duplicate to test mode
    root = insertNode(root, 70); // Another duplicate

    // Find and print the mode(s)
    printModes(root);

    return 0;
}
