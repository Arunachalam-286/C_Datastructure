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

// Helper function to convert BST to sorted DLL
void bstToDllUtil(struct Node* root, struct Node** head, struct Node** prev) {
    if (root == NULL) {
        return;
    }

    // Recur for the left subtree
    bstToDllUtil(root->left, head, prev);

    // Process the current node
    if (*prev == NULL) {
        // First node becomes the head of the DLL
        *head = root;
    } else {
        // Link the previous node with the current node
        (*prev)->right = root;
        root->left = *prev;
    }
    *prev = root; // Update the previous node

    // Recur for the right subtree
    bstToDllUtil(root->right, head, prev);
}

// Function to convert BST to sorted DLL
struct Node* bstToDll(struct Node* root) {
    struct Node* head = NULL;
    struct Node* prev = NULL;
    bstToDllUtil(root, &head, &prev);
    return head;
}

// Function to print the DLL from left to right
void printDll(struct Node* head) {
    struct Node* current = head;
    printf("Doubly Linked List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to print the DLL from right to left
void printDllReverse(struct Node* head) {
    if (head == NULL) {
        return;
    }

    // Move to the tail of the DLL
    struct Node* current = head;
    while (current->right != NULL) {
        current = current->right;
    }

    // Print the DLL in reverse order
    printf("Doubly Linked List in reverse: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->left;
    }
    printf("\n");
}

// Main function to demonstrate the conversion
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

    // Convert BST to sorted DLL
    struct Node* head = bstToDll(root);

    // Print the DLL
    printDll(head);
    printDllReverse(head);

    return 0;
}
