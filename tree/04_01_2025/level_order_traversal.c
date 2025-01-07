#include<stdio.h>
#include<stdlib.h>

// Define a binary tree node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert a node into the binary tree
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

// Function to perform inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the height of the binary tree
int height(struct Node *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Helper function to print nodes at a given level
void printLevel(struct Node *node, int level) {
    if (node == NULL) return;
    if (level == 1) {
        printf("%d ", node->data);
    } else if (level > 1) {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

// Function to perform level-order traversal
void levelOrder(struct Node *node) {
    int h = height(node);
    for (int i = 1; i <= h; i++) {
        printLevel(node, i);
    }
    printf("\n");
}

// Main function
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

    printf("Level-Order Traversal: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
