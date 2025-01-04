#include<stdio.h>
#include<stdlib.h>

// Define the Node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
}*root = NULL;

// Function to get the height of a node
int height(struct Node *node) {
    if (node == NULL) return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalance(struct Node *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// Function to perform a right rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    // Return new root
    return x;
}

// Function to perform a left rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    // Return new root
    return y;
}

// Function to insert a node and balance the tree
struct Node* insert(struct Node *node, int val) {
    // 1. Perform the normal BST insert
    if (node == NULL) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;  // New node is initially at height 1
        return newNode;
    }

    if (val < node->data) {
        node->left = insert(node->left, val);
    } else if (val > node->data) {
        node->right = insert(node->right, val);
    } else {
        // Duplicates are not allowed
        return node;
    }

    // 2. Update the height of this ancestor node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // 3. Get the balance factor of this node to check whether it became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && val < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && val > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && val > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && val < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Inorder traversal to print the tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Main function to drive the code
int main() {
    int val;
    printf("Enter values to insert into the AVL Tree (-1 to stop):\n");
    
    do {
        scanf("%d", &val);
        if (val != -1)
            root = insert(root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
