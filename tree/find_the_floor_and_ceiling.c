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

// Function to find the floor of a given key
int findFloor(struct Node* root, int key) {
    int floor = -1;
    while (root != NULL) {
        if (root->data == key) {
            return root->data;
        } else if (root->data < key) {
            floor = root->data;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return floor;
}

// Function to find the ceiling of a given key
int findCeiling(struct Node* root, int key) {
    int ceiling = -1;
    while (root != NULL) {
        if (root->data == key) {
            return root->data;
        } else if (root->data > key) {
            ceiling = root->data;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return ceiling;
}

// Main function to demonstrate finding floor and ceiling
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

    int key = 65; // Key to find floor and ceiling for

    int floor = findFloor(root, key);
    if (floor != -1) {
        printf("Floor of %d is %d\n", key, floor);
    } else {
        printf("Floor of %d does not exist.\n", key);
    }

    int ceiling = findCeiling(root, key);
    if (ceiling != -1) {
        printf("Ceiling of %d is %d\n", key, ceiling);
    } else {
        printf("Ceiling of %d does not exist.\n", key);
    }

    return 0;
}
