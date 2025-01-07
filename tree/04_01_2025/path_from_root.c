#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

int path[100];  // Array to store the path (assuming max depth is 100)
int pathLength = 0;

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

// Function to perform inorder traversal of the tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the path from root to a given node
int findPath(struct Node *node, int key) {
    if (node == NULL) {
        return 0;  // Base case: if node is NULL, return false
    }

    // Store this node in the path
    path[pathLength++] = node->data;

    // If the current node is the target node, return true
    if (node->data == key) {
        return 1;
    }

    // Otherwise, check if the target is in the left or right subtree
    if ((node->left && findPath(node->left, key)) || (node->right && findPath(node->right, key))) {
        return 1;
    }

    // If the node is not part of the path, backtrack (remove from path)
    pathLength--;
    return 0;
}

// Function to print the path from root to the given node
void printPath(int key) {
    if (findPath(root, key)) {
        printf("Path to %d: ", key);
        for (int i = 0; i < pathLength; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Node %d not found in the tree.\n", key);
    }
}

int main() {
    int val;
    printf("Enter values to construct the tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1) {
            insert(&root, val);
        }
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Test: Find the path to a given node (e.g., 15)
    int key;
    printf("Enter the value to find the path to: ");
    scanf("%d", &key);

    printPath(key);

    return 0;
}
