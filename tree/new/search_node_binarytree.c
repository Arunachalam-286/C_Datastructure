#include<stdio.h>
#include<stdlib.h>

// Define the structure for a node in the BST
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Function to insert a new value into the BST
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

// Recursive function for inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to search for a value in the BST
struct Node* search(struct Node *node, int key) {
    if (node == NULL || node->data == key) {
        return node;  // Node is NULL (not found) or key matches node's data
    }
    if (key < node->data) {
        return search(node->left, key);  // Search in the left subtree
    }
    return search(node->right, key);  // Search in the right subtree
}

int main() {
    int val, key;
    
    // Dynamically build the BST
    printf("Enter values to insert into the BST (-1 to stop): ");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Display the BST using inorder traversal
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Search for a value in the BST
    printf("Enter the value to search: ");
    scanf("%d", &key);
    struct Node *result = search(root, key);
    if (result != NULL) {
        printf("Value %d found in the BST.\n", key);
    } else {
        printf("Value %d not found in the BST.\n", key);
    }

    return 0;
}
