#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

int currentCount = 0;
int maxCount = 0;
int mode = -1;

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

// Helper function to handle mode calculation during inorder traversal
void inorderTraversal(struct Node *node) {
    if (node == NULL) return;
    
    // Traverse left subtree
    inorderTraversal(node->left);

    // Update frequency count of the current value
    if (node->data == mode) {
        currentCount++;
    } else {
        mode = node->data;
        currentCount = 1;
    }

    // Update the mode if needed
    if (currentCount > maxCount) {
        maxCount = currentCount;
    }

    // Traverse right subtree
    inorderTraversal(node->right);
}

// Function to find and return the mode
void findMode(struct Node *node) {
    currentCount = 0;
    maxCount = 0;
    mode = -1;

    inorderTraversal(node);
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    findMode(root);

    printf("Mode: %d\n", mode);

    return 0;
}
