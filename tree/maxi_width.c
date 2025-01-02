#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// A structure for the queue used in level-order traversal
struct QueueNode {
    struct TreeNode* node;
    int index;  // Position of the node in the level
    struct QueueNode* next;
};

// A structure for the queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to enqueue a node with its index
void enqueue(struct Queue* queue, struct TreeNode* node, int index) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->node = node;
    newNode->index = index;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a node
struct QueueNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return temp;
}

// Function to find the maximum width of a binary tree
int maxWidth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    // Queue for level-order traversal
    struct Queue* queue = createQueue();
    enqueue(queue, root, 0); // Root has index 0

    int maxWidth = 0;

    while (queue->front != NULL) {
        int size = 0;
        int firstIndex = queue->front->index;

        // Process all nodes at the current level
        while (queue->front != NULL && queue->front->index < firstIndex + size) {
            struct QueueNode* node = dequeue(queue);
            size++;

            // Enqueue left child with index 2*index (for left child)
            if (node->node->left != NULL) {
                enqueue(queue, node->node->left, 2 * node->index + 1);
            }

            // Enqueue right child with index 2*index + 1 (for right child)
            if (node->node->right != NULL) {
                enqueue(queue, node->node->right, 2 * node->index + 2);
            }
        }

        // The width of the current level is the difference between the first and last indices
        int lastIndex = queue->rear != NULL ? queue->rear->index : firstIndex;
        maxWidth = (lastIndex - firstIndex + 1) > maxWidth ? (lastIndex - firstIndex + 1) : maxWidth;
    }

    return maxWidth;
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->right = createTreeNode(6);
    root->left->left->left = createTreeNode(7);

    // Find the maximum width of the tree
    int width = maxWidth(root);
    printf("Maximum width of the binary tree is: %d\n", width);

    return 0;
}
