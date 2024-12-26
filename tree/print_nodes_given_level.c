#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Definition of a queue node
typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

// Function to create a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to enqueue a tree node
void enqueue(QueueNode** front, QueueNode** rear, TreeNode* node) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->node = node;
    newQueueNode->next = NULL;
    if (*rear) {
        (*rear)->next = newQueueNode;
    } else {
        *front = newQueueNode;
    }
    *rear = newQueueNode;
}

// Function to dequeue a tree node
TreeNode* dequeue(QueueNode** front, QueueNode** rear) {
    if (*front == NULL) return NULL;
    QueueNode* temp = *front;
    TreeNode* node = temp->node;
    *front = temp->next;
    if (*front == NULL) *rear = NULL;
    free(temp);
    return node;
}

// Function to print nodes at a given level iteratively
void printLevelIterative(TreeNode* root, int level) {
    if (root == NULL) return;

    QueueNode* front = NULL;
    QueueNode* rear = NULL;
    enqueue(&front, &rear, root);

    int currentLevel = 1;
    while (front != NULL) {
        int nodeCount = 0;

        // Count nodes at the current level
        for (QueueNode* temp = front; temp != NULL; temp = temp->next) nodeCount++;

        // If we are at the desired level, print all nodes
        if (currentLevel == level) {
            for (int i = 0; i < nodeCount; i++) {
                TreeNode* current = dequeue(&front, &rear);
                printf("%d ", current->val);

                // Re-enqueue the children, if necessary
                if (current->left) enqueue(&front, &rear, current->left);
                if (current->right) enqueue(&front, &rear, current->right);
            }
            return;
        }

        // Otherwise, process all nodes at this level
        for (int i = 0; i < nodeCount; i++) {
            TreeNode* current = dequeue(&front, &rear);
            if (current->left) enqueue(&front, &rear, current->left);
            if (current->right) enqueue(&front, &rear, current->right);
        }

        currentLevel++;
    }
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    int level = 3;
    printf("Nodes at level %d: ", level);
    printLevelIterative(root, level);
    printf("\n");

    // Free memory (optional for small programs)
    free(root->left->left);
    free(root->left->right);
    free(root->right->left);
    free(root->right->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
