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

// Function to calculate the height of a tree
int height(struct Node *node) {
    if (node == NULL)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to check if a tree is balanced
int isBalanced(struct Node *node) {
    if (node == NULL)
        return 1;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right))
        return 1;

    return 0;
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

    if (isBalanced(root)) {
        printf("The binary tree is balanced.\n");
    } else {
        printf("The binary tree is not balanced.\n");
    }

    return 0;
}
