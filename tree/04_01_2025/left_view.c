#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

int maxLevel = 0; // Keeps track of the max level visited so far

void insert(struct Node **node, int val) {
    // 1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    // 2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Helper function to print the left view of the tree
void printLeftViewUtil(struct Node *node, int level) {
    // Base case
    if (node == NULL) {
        return;
    }

    // If this is the first node of this level, print it
    if (level > maxLevel) {
        printf("%d ", node->data);
        maxLevel = level;
    }

    // Recur for left and right subtrees
    printLeftViewUtil(node->left, level + 1);
    printLeftViewUtil(node->right, level + 1);
}

// Function to print the left view of the binary tree
void printLeftView(struct Node *node) {
    maxLevel = 0; // Reset maxLevel before printing
    printLeftViewUtil(node, 1); // Start from level 1
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
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

    printf("Left View of the Binary Tree: ");
    printLeftView(root);
    printf("\n");

    return 0;
}
