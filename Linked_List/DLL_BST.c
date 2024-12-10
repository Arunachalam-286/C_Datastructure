#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Definition of a doubly linked list node
struct DLLNode {
    int data;
    struct DLLNode* prev;
    struct DLLNode* next;
};

// Function to create a new tree node
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a new DLL node
struct DLLNode* createDLLNode(int data) {
    struct DLLNode* newNode = (struct DLLNode*)malloc(sizeof(struct DLLNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Global pointer to track the previous node in the DLL
struct DLLNode* prevNode = NULL;

// Function to convert a binary tree to a doubly linked list
struct DLLNode* binaryTreeToDLL(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    // Head of the doubly linked list
    static struct DLLNode* head = NULL;

    // Recursively convert the left subtree
    binaryTreeToDLL(root->left);

    // Process the current tree node
    struct DLLNode* current = createDLLNode(root->data);

    if (prevNode == NULL) {
        // This is the leftmost node, so it's the head of the DLL
        head = current;
    } else {
        // Link the previous node with the current node
        prevNode->next = current;
        current->prev = prevNode;
    }

    // Update the previous node to the current node
    prevNode = current;

    // Recursively convert the right subtree
    binaryTreeToDLL(root->right);

    return head;
}

// Function to print the doubly linked list
void printDLL(struct DLLNode* head) {
    printf("Doubly Linked List: ");
    struct DLLNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Example usage
int main() {
    // Create a binary tree
    struct TreeNode* root = createTreeNode(10);
    root->left = createTreeNode(6);
    root->right = createTreeNode(15);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(8);
    root->right->left = createTreeNode(12);
    root->right->right = createTreeNode(18);

    // Convert the binary tree to a doubly linked list
    struct DLLNode* head = binaryTreeToDLL(root);

    // Print the doubly linked list
    printDLL(head);

    return 0;
}