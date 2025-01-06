#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

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

void printPath(int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Helper function to find paths recursively
void findPathsHelper(struct Node *node, int targetSum, int currentSum, int path[], int pathLen) {
    if (node == NULL) {
        return;
    }

    // Add current node to path
    path[pathLen] = node->data;
    pathLen++;
    currentSum += node->data;

    // If currentSum matches targetSum, print the path
    if (currentSum == targetSum) {
        printPath(path, pathLen);
    }

    // Traverse left and right children
    findPathsHelper(node->left, targetSum, currentSum, path, pathLen);
    findPathsHelper(node->right, targetSum, currentSum, path, pathLen);
}

// Function to find all paths that sum to a given value
void findPaths(struct Node *node, int targetSum) {
    int path[1000];  // We can assume the maximum length of any path won't exceed 1000
    findPathsHelper(node, targetSum, 0, path, 0);
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val, targetSum;

    // Construct tree
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Get the target sum from user
    printf("Enter the target sum: ");
    scanf("%d", &targetSum);

    // Inorder Traversal
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Find all paths with the given sum
    printf("Paths that sum to %d:\n", targetSum);
    findPaths(root, targetSum);

    return 0;
}
