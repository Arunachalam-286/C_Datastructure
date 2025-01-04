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

// Function to calculate the height of the binary tree
int height(struct Node *node) {
    if (node == NULL) {
        return -1;  // Base case: height of empty tree is -1
    }
    int leftHeight = height(node->left);   // Height of left subtree
    int rightHeight = height(node->right); // Height of right subtree

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); // Max height of both subtrees + 1
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

    // Calculate and display the height of the binary tree
    int treeHeight = height(root);
    printf("Height of the Binary Tree: %d\n", treeHeight);

    return 0;
}
