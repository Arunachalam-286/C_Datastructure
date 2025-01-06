#include<stdio.h>
#include<stdlib.h>
#define MAX_NODES 1000 // To handle a range of HD from -500 to +500

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Array to store the top view values, initialized with -1
int topView[MAX_NODES];
int minHD = 500, maxHD = 500; // To track the range of HD

// Initialize the topView array
void initializeTopView() {
    for (int i = 0; i < MAX_NODES; i++) {
        topView[i] = -1;
    }
}

// Insert a new node into the binary tree
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

// Recursive function to calculate top view
void calculateTopView(struct Node *node, int hd) {
    if (node == NULL) return;

    // Check and store the first node at this horizontal distance
    int index = hd + 500; // Shift HD to handle negative values
    if (topView[index] == -1) {
        topView[index] = node->data;
        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;
    }

    // Recur for left and right subtrees
    calculateTopView(node->left, hd - 1);
    calculateTopView(node->right, hd + 1);
}

// Print the top view of the tree
void printTopView() {
    for (int i = minHD + 500; i <= maxHD + 500; i++) {
        if (topView[i] != -1) {
            printf("%d ", topView[i]);
        }
    }
    printf("\n");
}

int main() {
    initializeTopView();

    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    calculateTopView(root, 0);

    printf("Top View: ");
    printTopView();

    return 0;
}
