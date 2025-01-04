#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Function to insert a new node into the binary tree
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

// Function to perform inorder traversal of the binary tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to calculate the sum of all nodes in the binary tree
int sumOfNodes(struct Node *node) {
    if (node == NULL) return 0;
    return node->data + sumOfNodes(node->left) + sumOfNodes(node->right);
}

int main() {
    int val;
    // Insert nodes into the binary tree
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Perform inorder traversal
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Calculate and display the sum of all nodes
    int totalSum = sumOfNodes(root);
    printf("Sum of all nodes: %d\n", totalSum);

    return 0;
}
