#include<stdio.h>
#include<stdlib.h>

// Define the structure of a tree node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to create and insert a new node into the binary tree
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

// Function to perform inorder traversal of the tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Helper function to check if the tree is height-balanced
// Returns the height of the subtree if balanced, or -1 if not balanced
int isBalancedHelper(struct Node *node) {
    if (node == NULL) return 0;

    // Recursively check the left and right subtrees
    int leftHeight = isBalancedHelper(node->left);
    if (leftHeight == -1) return -1;

    int rightHeight = isBalancedHelper(node->right);
    if (rightHeight == -1) return -1;

    // Check if the current node is balanced
    if (abs(leftHeight - rightHeight) > 1) return -1;

    // Return the height of the current node
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to check if the binary tree is height-balanced
int isBalanced(struct Node *root) {
    return isBalancedHelper(root) != -1;
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
        printf("The binary tree is height-balanced.\n");
    } else {
        printf("The binary tree is not height-balanced.\n");
    }

    return 0;
}
