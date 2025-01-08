#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert nodes into the binary tree
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

// Function for inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Helper function to calculate height of a tree
int height(struct Node *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to calculate the diameter of the binary tree
int diameter(struct Node *node, int *maxDiameter) {
    if (node == NULL) return 0;

    // Calculate the height of left and right subtrees
    int leftHeight = diameter(node->left, maxDiameter);
    int rightHeight = diameter(node->right, maxDiameter);

    // Update the maximum diameter if the current diameter is greater
    int currentDiameter = leftHeight + rightHeight;
    if (currentDiameter > *maxDiameter) {
        *maxDiameter = currentDiameter;
    }

    // Return the height of the current subtree
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Find the diameter of the binary tree
    int maxDiameter = 0;
    diameter(root, &maxDiameter);
    printf("Diameter of the binary tree: %d\n", maxDiameter);

    return 0;
}
