#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

void insert(struct Node **node, int val) {
    // 1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    // 2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to count nodes at each level
void countNodesAtLevel(struct Node *node, int level, int *count) {
    if (node == NULL)
        return;

    // Increment the count for the current level
    count[level]++;

    // Recur for left and right subtrees
    countNodesAtLevel(node->left, level + 1, count);
    countNodesAtLevel(node->right, level + 1, count);
}

// Function to find the height of the tree
int treeHeight(struct Node *node) {
    if (node == NULL)
        return 0;
    int leftHeight = treeHeight(node->left);
    int rightHeight = treeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    int val;
    int levelCount[100] = {0};  // Array to store count of nodes at each level

    // Insert values into the binary tree
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Find the height of the tree
    int height = treeHeight(root);

    // Count nodes at each level
    countNodesAtLevel(root, 0, levelCount);

    // Print the count of nodes at each level
    printf("Node count at each level:\n");
    for (int i = 0; i < height; i++) {
        printf("Level %d: %d nodes\n", i, levelCount[i]);
    }

    return 0;
}
