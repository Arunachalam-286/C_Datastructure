#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

struct Node *head = NULL; // Head of the doubly linked list
struct Node *prev = NULL; // Pointer to the previous node in DLL

// Function to insert a node in the BST
void insert(struct Node **node, int val) {
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to convert BST to a sorted Doubly Linked List
void bstToDoublyLinkedList(struct Node *node) {
    if (node == NULL) return;

    // Recursively convert the left subtree
    bstToDoublyLinkedList(node->left);

    // Process the current node
    if (prev == NULL) {
        // This is the first node, make it the head of the DLL
        head = node;
    } else {
        // Link the previous node with the current node
        prev->right = node;
        node->left = prev;
    }
    prev = node;

    // Recursively convert the right subtree
    bstToDoublyLinkedList(node->right);
}

// Function to print the Doubly Linked List
void printDoublyLinkedList(struct Node *node) {
    printf("Doubly Linked List: ");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->right;
    }
    printf("\n");
}

// Function to print the BST using inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val;

    // Insert nodes into the BST
    printf("Enter values to insert into BST (-1 to stop): ");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Perform inorder traversal of the BST
    printf("Inorder Traversal of BST: ");
    inorder(root);
    printf("\n");

    // Convert BST to sorted Doubly Linked List
    bstToDoublyLinkedList(root);

    // Print the Doubly Linked List
    printDoublyLinkedList(head);

    return 0;
}
