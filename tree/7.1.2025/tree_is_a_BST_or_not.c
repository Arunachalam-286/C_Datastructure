#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the Node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Function to insert a node into the binary tree
void insert(struct Node **node, int val) {
    // If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    // Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to perform an inorder traversal
void inorder(struct Node *node) {
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to check if a binary tree is a binary search tree
int isBSTUtil(struct Node *node, int min, int max) {
    // An empty tree is a BST
    if (node == NULL)
        return 1;

    // Check if the current node violates the min/max constraints
    if (node->data <= min || node->data >= max)
        return 0;

    // Recursively check the left and right subtrees
    return isBSTUtil(node->left, min, node->data) &&
           isBSTUtil(node->right, node->data, max);
}

// Wrapper function to check if the tree is a BST
int isBST(struct Node *root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Main function
int main() {
    int val;
    // Input values to build the tree
    printf("Enter values to insert into the tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Display the inorder traversal of the tree
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Check if the tree is a BST
    if (isBST(root)) {
        printf("The tree is a Binary Search Tree.\n");
    } else {
        printf("The tree is NOT a Binary Search Tree.\n");
    }

    return 0;
}
