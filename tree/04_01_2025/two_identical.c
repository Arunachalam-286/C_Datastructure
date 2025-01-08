#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Global pointers for two trees
struct Node *root1 = NULL;
struct Node *root2 = NULL;

// Function to insert a node in the binary tree
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

// Function for inorder traversal of a binary tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to check if two binary trees are identical
int areIdentical(struct Node *root1, struct Node *root2) {
    // Base cases
    if (root1 == NULL && root2 == NULL)
        return 1; // Both trees are empty, so they are identical
    if (root1 == NULL || root2 == NULL)
        return 0; // One tree is empty, and the other is not, so they are not identical
    
    // Check current nodes' data and recursively check their subtrees
    return (root1->data == root2->data &&
            areIdentical(root1->left, root2->left) &&
            areIdentical(root1->right, root2->right));
}

int main() {
    int val;

    // Input for the first tree
    printf("Enter values for the first tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root1, val);
    } while (val != -1);

    printf("Inorder Traversal of First Tree: ");
    inorder(root1);
    printf("\n");

    // Input for the second tree
    printf("Enter values for the second tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root2, val);
    } while (val != -1);

    printf("Inorder Traversal of Second Tree: ");
    inorder(root2);
    printf("\n");

    // Check if the two trees are identical
    if (areIdentical(root1, root2)) {
        printf("The two trees are identical.\n");
    } else {
        printf("The two trees are not identical.\n");
    }

    return 0;
}
