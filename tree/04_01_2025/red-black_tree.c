#include<stdio.h>
#include<stdlib.h>

#define RED 0
#define BLACK 1

struct Node {
    int data;
    int color;  // 0 -> Red, 1 -> Black
    struct Node *left;
    struct Node *right;
    struct Node *parent;
}*root = NULL;

// Function to create a new node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->color = RED;  // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Right rotation function
void rotateRight(struct Node** root, struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    
    if (y->right != NULL) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

// Left rotation function
void rotateLeft(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    
    if (y->left != NULL) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

// Fix violation of Red-Black Tree properties after insertion
void fixInsertion(struct Node** root, struct Node* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node* y = z->parent->parent->right;
            
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2 and Case 3: Uncle is black
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            struct Node* y = z->parent->parent->left;
            
            if (y != NULL && y->color == RED) {
                // Case 1: Uncle is red
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // Case 2 and Case 3: Uncle is black
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    
    (*root)->color = BLACK;
}

// Insertion function
void insert(struct Node** root, int val) {
    struct Node* z = createNode(val);
    struct Node* y = NULL;
    struct Node* x = *root;
    
    while (x != NULL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NULL) {
        *root = z;  // Tree was empty
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    fixInsertion(root, z);
}

// Inorder Traversal (used for display)
void inorder(struct Node* node) {
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

    return 0;
}
