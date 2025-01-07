#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// Define the structure for the tree node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Structure to store information about the largest BST
struct Info {
    int size;      // Size of the current subtree
    int max;       // Maximum value in the subtree
    int min;       // Minimum value in the subtree
    int largestBSTSize; // Size of the largest BST in the subtree
    int isBST;     // 1 if the subtree is a BST, 0 otherwise
};

// Insert a new node in the binary tree
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

// Helper function to calculate the largest BST in a binary tree
struct Info largestBST(struct Node *node) {
    // Base case: If the node is NULL, it's a BST of size 0
    if (node == NULL) {
        return (struct Info){0, INT_MIN, INT_MAX, 0, 1};
    }

    // Recursively find info for left and right subtrees
    struct Info leftInfo = largestBST(node->left);
    struct Info rightInfo = largestBST(node->right);

    struct Info curr;
    curr.size = leftInfo.size + rightInfo.size + 1;

    // Check if the current subtree is a BST
    if (leftInfo.isBST && rightInfo.isBST && 
        node->data > leftInfo.max && node->data < rightInfo.min) {
        curr.min = (node->left != NULL) ? leftInfo.min : node->data;
        curr.max = (node->right != NULL) ? rightInfo.max : node->data;
        curr.largestBSTSize = curr.size;
        curr.isBST = 1;
        return curr;
    }

    // If not a BST, return the largest BST size in the subtrees
    curr.largestBSTSize = (leftInfo.largestBSTSize > rightInfo.largestBSTSize) 
                           ? leftInfo.largestBSTSize 
                           : rightInfo.largestBSTSize;
    curr.isBST = 0;
    return curr;
}

// Perform inorder traversal to display the tree
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

    struct Info result = largestBST(root);
    printf("Size of the largest BST subtree: %d\n", result.largestBSTSize);

    return 0;
}
