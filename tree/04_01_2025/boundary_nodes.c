#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

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

void printLeftBoundary(struct Node *node) {
    if (node == NULL) return;
    if (node->left) {
        printf("%d ", node->data);
        printLeftBoundary(node->left);
    } else if (node->right) {
        printf("%d ", node->data);
        printLeftBoundary(node->right);
    }
}

void printRightBoundary(struct Node *node) {
    if (node == NULL) return;
    if (node->right) {
        printRightBoundary(node->right);
        printf("%d ", node->data);
    } else if (node->left) {
        printRightBoundary(node->left);
        printf("%d ", node->data);
    }
}

void printLeaves(struct Node *node) {
    if (node == NULL) return;
    printLeaves(node->left);
    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->data);
    }
    printLeaves(node->right);
}

void printBoundary(struct Node *root) {
    if (root == NULL) return;
    
    // Print root node
    printf("%d ", root->data);
    
    // Print left boundary (excluding root)
    printLeftBoundary(root->left);
    
    // Print leaf nodes
    printLeaves(root);
    
    // Print right boundary (excluding root and leaves)
    printRightBoundary(root->right);
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Boundary Nodes: ");
    printBoundary(root);
    printf("\n");

    return 0;
}
