#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert a node into the binary tree
void insert(struct Node **node, int val) {
    // If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    // Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to perform diagonal traversal
void diagonalTraversalUtil(struct Node *node, int d, int diagonal[], int *maxDiagonal) {
    if (node == NULL) return;

    // Store the node data at the current diagonal level
    diagonal[d] = node->data;
    *maxDiagonal = d > *maxDiagonal ? d : *maxDiagonal;

    // Recurse for left subtree with diagonal + 1
    if (node->left) {
        diagonalTraversalUtil(node->left, d + 1, diagonal, maxDiagonal);
    }

    // Recurse for right subtree with the same diagonal level
    if (node->right) {
        diagonalTraversalUtil(node->right, d, diagonal, maxDiagonal);
    }
}

// Function to print diagonal traversal
void diagonalTraversal(struct Node *root) {
    // To store the nodes in each diagonal
    int diagonal[100];
    int maxDiagonal = 0;

    diagonalTraversalUtil(root, 0, diagonal, &maxDiagonal);

    // Printing diagonal traversal for each diagonal level
    for (int i = 0; i <= maxDiagonal; i++) {
        printf("Diagonal %d: ", i);
        for (int j = i; j <= maxDiagonal; j++) {
            if (diagonal[j] != 0) {
                printf("%d ", diagonal[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Perform the diagonal traversal
    printf("Diagonal Traversal:\n");
    diagonalTraversal(root);
    return 0;
}
