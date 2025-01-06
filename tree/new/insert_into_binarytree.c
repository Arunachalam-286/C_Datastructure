#include<stdio.h>
#include<stdlib.h>

// Define the structure of a Node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert a node into the BST
void insert(struct Node **node, int val) {
    //1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    //2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to perform inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to perform preorder traversal
void preorder(struct Node *node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Function to perform postorder traversal
void postorder(struct Node *node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

int main() {
    int val;

    // Insert nodes into the BST
    printf("Enter values to insert into the BST (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Perform traversals
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
