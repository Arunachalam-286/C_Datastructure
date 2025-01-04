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

// Function to print all leaf nodes of the binary tree
void printLeafNodes(struct Node *node) {
    if (node == NULL) return;
    
    // If both left and right children are NULL, then it's a leaf node
    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->data);
    }

    // Recursively print leaf nodes of left and right subtrees
    printLeafNodes(node->left);
    printLeafNodes(node->right);
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

    printf("Leaf Nodes: ");
    printLeafNodes(root);
    printf("\n");

    return 0;
}
