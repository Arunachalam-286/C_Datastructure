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

// Function to calculate the sum of all nodes iteratively
int sumOfNodesIterative(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    QueueNode* front = NULL;
    QueueNode* rear = NULL;

    enqueue(&front, &rear, root);

    while (front != NULL) {
        TreeNode* current = dequeue(&front, &rear);

        // Add current node value to sum
        sum += current->val;

        // Enqueue left and right children
        if (current->left) enqueue(&front, &rear, current->left);
        if (current->right) enqueue(&front, &rear, current->right);
    }

    return sum;
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // Calculate and print the sum of all nodes
    printf("Sum of all nodes in the binary tree: %d\n", sumOfNodesIterative(root));

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
