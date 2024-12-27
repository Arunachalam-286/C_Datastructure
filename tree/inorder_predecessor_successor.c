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

// Helper function to find the maximum value in a subtree
struct Node* findMax(struct Node* node) {
    while (node && node->right != NULL) {
        node = node->right;
    }
    return node;
}

// Helper function to find the minimum value in a subtree
struct Node* findMin(struct Node* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to find the inorder predecessor and successor of a given key
void findPredecessorSuccessor(struct Node* root, struct Node** predecessor, struct Node** successor, int key) {
    if (root == NULL) {
        return;
    }

    if (root->data == key) {
        // If the left subtree exists, the predecessor is the max in the left subtree
        if (root->left != NULL) {
            *predecessor = findMax(root->left);
        }
        // If the right subtree exists, the successor is the min in the right subtree
        if (root->right != NULL) {
            *successor = findMin(root->right);
        }
        return;
    }

    if (key < root->data) {
        *successor = root; // Update successor to current node
        findPredecessorSuccessor(root->left, predecessor, successor, key);
    } else {
        *predecessor = root; // Update predecessor to current node
        findPredecessorSuccessor(root->right, predecessor, successor, key);
    }
}

// Function to perform in-order traversal of the BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Main function to demonstrate finding predecessor and successor
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

    // Perform in-order traversal
    printf("In-order traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    int key = 65; // Key to find predecessor and successor for
    struct Node* predecessor = NULL;
    struct Node* successor = NULL;

    findPredecessorSuccessor(root, &predecessor, &successor, key);

    if (predecessor != NULL) {
        printf("Predecessor of %d is %d\n", key, predecessor->data);
    } else {
        printf("Predecessor of %d does not exist.\n", key);
    }

    if (successor != NULL) {
        printf("Successor of %d is %d\n", key, successor->data);
    } else {
        printf("Successor of %d does not exist.\n", key);
    }

    return 0;
}
