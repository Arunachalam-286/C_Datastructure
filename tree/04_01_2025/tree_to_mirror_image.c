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

void mirrorTree(struct Node *node) {
    if (node == NULL) return;

    // Swap left and right subtrees
    struct Node *temp = node->left;
    node->left = node->right;
    node->right = temp;

    // Recursively mirror the left and right subtrees
    mirrorTree(node->left);
    mirrorTree(node->right);
}

int main() {
    int val;

    // Building the tree
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Original tree
    printf("Inorder Traversal of Original Tree: ");
    inorder(root);
    printf("\n");

    // Convert to mirror image
    mirrorTree(root);

    // Mirrored tree
    printf("Inorder Traversal of Mirrored Tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
