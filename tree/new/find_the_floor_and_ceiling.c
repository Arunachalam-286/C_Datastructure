#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert a node into the BST
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

// Function to perform inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the floor of a given key
int findFloor(struct Node *node, int key) {
    int floor = -1; // Initialize floor as -1 (assuming all keys are positive)
    while (node) {
        if (node->data == key) {
            return node->data; // If the key matches, it is its own floor
        }
        if (key > node->data) {
            floor = node->data; // Update floor and move to the right subtree
            node = node->right;
        } else {
            node = node->left; // Move to the left subtree
        }
    }
    return floor; // Return the final floor value
}

// Function to find the ceiling of a given key
int findCeiling(struct Node *node, int key) {
    int ceiling = -1; // Initialize ceiling as -1 (assuming all keys are positive)
    while (node) {
        if (node->data == key) {
            return node->data; // If the key matches, it is its own ceiling
        }
        if (key < node->data) {
            ceiling = node->data; // Update ceiling and move to the left subtree
            node = node->left;
        } else {
            node = node->right; // Move to the right subtree
        }
    }
    return ceiling; // Return the final ceiling value
}

int main() {
    int val, key;
    printf("Enter elements of BST (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Enter the key to find floor and ceiling: ");
    scanf("%d", &key);

    int floor = findFloor(root, key);
    int ceiling = findCeiling(root, key);

    printf("Floor of %d: %d\n", key, floor == -1 ? -1 : floor);
    printf("Ceiling of %d: %d\n", key, ceiling == -1 ? -1 : ceiling);

    return 0;
}
