#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

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

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the minimum value in the binary tree
int findMin(struct Node *node) {
    if (node == NULL) {
        printf("The tree is empty.\n");
        return -1; // Indicate an empty tree
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node->data;
}

// Function to find the maximum value in the binary tree
int findMax(struct Node *node) {
    if (node == NULL) {
        printf("The tree is empty.\n");
        return -1; // Indicate an empty tree
    }
    while (node->right != NULL) {
        node = node->right;
    }
    return node->data;
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

    int minVal = findMin(root);
    int maxVal = findMax(root);

    printf("Minimum value in the tree: %d\n", minVal);
    printf("Maximum value in the tree: %d\n", maxVal);

    return 0;
}
