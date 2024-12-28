#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive function to find the level and parent of a target node
void findLevelAndParent(struct Node* root, int target, int level, struct Node** parent, int* targetLevel) {
    if (root == NULL)
        return;

    if (root->left && root->left->data == target) {
        *parent = root;
        *targetLevel = level + 1;
        return;
    }

    if (root->right && root->right->data == target) {
        *parent = root;
        *targetLevel = level + 1;
        return;
    }

    findLevelAndParent(root->left, target, level + 1, parent, targetLevel);
    findLevelAndParent(root->right, target, level + 1, parent, targetLevel);
}

// Function to check if two nodes are cousins
int areCousins(struct Node* root, int x, int y) {
    if (root == NULL)
        return 0;

    struct Node* parentX = NULL;
    struct Node* parentY = NULL;
    int levelX = -1, levelY = -1;

    // Find parent and level of x and y
    findLevelAndParent(root, x, 0, &parentX, &levelX);
    findLevelAndParent(root, y, 0, &parentY, &levelY);

    // Check if x and y are at the same level but have different parents
    return (levelX == levelY && parentX != parentY);
}

// Main function
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int x = 4, y = 6;

    if (areCousins(root, x, y))
        printf("%d and %d are cousins.\n", x, y);
    else
        printf("%d and %d are not cousins.\n", x, y);

    return 0;
}
