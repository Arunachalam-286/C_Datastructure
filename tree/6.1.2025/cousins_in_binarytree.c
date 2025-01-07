#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Function to insert a node into the binary tree
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

// Inorder traversal function
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the level of a node and its parent
int findLevelAndParent(struct Node *node, int val, int level, struct Node **parent) {
    if (node == NULL) return -1;

    if ((node->left && node->left->data == val) || (node->right && node->right->data == val)) {
        *parent = node;
        return level + 1;
    }

    int leftLevel = findLevelAndParent(node->left, val, level + 1, parent);
    if (leftLevel != -1) return leftLevel;

    return findLevelAndParent(node->right, val, level + 1, parent);
}

// Function to check if two nodes are cousins
int areCousins(struct Node *root, int val1, int val2) {
    if (root == NULL) return 0;

    struct Node *parent1 = NULL, *parent2 = NULL;
    int level1 = findLevelAndParent(root, val1, 0, &parent1);
    int level2 = findLevelAndParent(root, val2, 0, &parent2);

    // Check if levels are the same and parents are different
    return (level1 == level2 && parent1 != parent2);
}

int main() {
    int val;
    printf("Enter values to create a binary tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    int node1, node2;
    printf("Enter two nodes to check if they are cousins: ");
    scanf("%d %d", &node1, &node2);

    if (areCousins(root, node1, node2)) {
        printf("Nodes %d and %d are cousins.\n", node1, node2);
    } else {
        printf("Nodes %d and %d are not cousins.\n", node1, node2);
    }

    return 0;
}
