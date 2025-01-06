#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

void insert(struct Node **node, int val) {
    //1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    //2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Helper function to calculate the height of a subtree
int calculateHeight(struct Node *node) {
    if (node == NULL) return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Recursive function to calculate the burning time
int burnTree(struct Node *node, int target, int *timeToReachTarget, int *maxBurnTime) {
    if (node == NULL) return 0;

    if (node->data == target) {
        *timeToReachTarget = 0; // Time to reach the target node is 0
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        *maxBurnTime = leftHeight > rightHeight ? leftHeight : rightHeight;
        return 1; // Start the upward propagation
    }

    int leftTime = -1, rightTime = -1;

    // Check in the left subtree
    int leftBurnTime = burnTree(node->left, target, &leftTime, maxBurnTime);
    if (leftTime != -1) {
        int totalTime = leftTime + 1 + calculateHeight(node->right);
        if (totalTime > *maxBurnTime) {
            *maxBurnTime = totalTime;
        }
        return leftBurnTime + 1;
    }

    // Check in the right subtree
    int rightBurnTime = burnTree(node->right, target, &rightTime, maxBurnTime);
    if (rightTime != -1) {
        int totalTime = rightTime + 1 + calculateHeight(node->left);
        if (totalTime > *maxBurnTime) {
            *maxBurnTime = totalTime;
        }
        return rightBurnTime + 1;
    }

    return 0;
}

// Function to find the burn time starting from the target node
int findBurnTime(struct Node *root, int target) {
    int timeToReachTarget = -1;
    int maxBurnTime = 0;

    burnTree(root, target, &timeToReachTarget, &maxBurnTime);
    return maxBurnTime;
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

    int target;
    printf("Enter the target node: ");
    scanf("%d", &target);

    int burnTime = findBurnTime(root, target);
    printf("Time to burn the entire tree starting from node %d: %d\n", target, burnTime);

    return 0;
}
