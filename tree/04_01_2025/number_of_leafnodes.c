#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Function to insert a node into the binary tree
void insert(struct Node **node, int val) {
    // If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
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

// Inorder traversal of the tree (for displaying the tree in sorted order)
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to count the number of leaf nodes in the binary tree
int countLeafNodes(struct Node *node) {
    // If the node is NULL, return 0
    if (node == NULL) {
        return 0;
    }
    // If the node is a leaf (no left or right child), return 1
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    // Otherwise, count leaf nodes in both subtrees
    return countLeafNodes(node->left) + countLeafNodes(node->right);
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Inorder Traversal of the tree
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Counting leaf nodes
    int leafCount = countLeafNodes(root);
    printf("Number of leaf nodes: %d\n", leafCount);

    return 0;
}
