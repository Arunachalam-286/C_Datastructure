#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Helper function to find the minimum value in a subtree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a node in the BST
struct Node* deleteNode(struct Node* node, int key) {
    if (node == NULL)
        return node;

    // Traverse to the left or right based on the key
    if (key < node->data) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->data) {
        node->right = deleteNode(node->right, key);
    } else {
        // Node with one or no child
        if (node->left == NULL) {
            struct Node* temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct Node* temp = node->left;
            free(node);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(node->right);

        // Copy the inorder successor's data to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}

// Function to insert a node in the BST
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

// Inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val, delKey;
    
    // Insert nodes into the BST
    printf("Enter values to insert into BST (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Display the BST
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Delete nodes from the BST
    printf("Enter a value to delete (-1 to stop):\n");
    do {
        scanf("%d", &delKey);
        if (delKey != -1) {
            root = deleteNode(root, delKey);
            printf("Inorder Traversal after deleting %d: ", delKey);
            inorder(root);
            printf("\n");
        }
    } while (delKey != -1);

    return 0;
}
