#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Structure to store bottom view data
struct BottomView {
    int hd;      // Horizontal distance
    int level;   // Depth level
    int value;   // Node value
} bottom[1000]; // Assuming max HD range (-500 to 500)

// To initialize the bottom view array
void initializeBottomView() {
    for (int i = 0; i < 1000; i++) {
        bottom[i].hd = -1;
        bottom[i].level = -1;
        bottom[i].value = 0;
    }
}

// Insert a node in the binary tree
void insert(struct Node **node, int val) {
    if (*node == NULL) {
        struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
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

// Function to compute the bottom view recursively
void computeBottomView(struct Node *node, int hd, int level) {
    if (node == NULL) return;

    int index = hd + 500; // Shift HD to positive index range
    if (bottom[index].hd == -1 || level >= bottom[index].level) {
        bottom[index].hd = hd;
        bottom[index].level = level;
        bottom[index].value = node->data;
    }

    // Traverse left and right subtrees
    computeBottomView(node->left, hd - 1, level + 1);
    computeBottomView(node->right, hd + 1, level + 1);
}

// Function to print the bottom view
void printBottomView() {
    for (int i = 0; i < 1000; i++) {
        if (bottom[i].hd != -1) {
            printf("%d ", bottom[i].value);
        }
    }
    printf("\n");
}

// Inorder traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    initializeBottomView();

    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    computeBottomView(root, 0, 0); // Start from root with HD = 0 and level = 0

    printf("Bottom View: ");
    printBottomView();

    return 0;
}
