#include <stdio.h>
#include <stdlib.h>

// Define the structure of a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Define the structure of a queue node
typedef struct QueueNode {
    TreeNode* node;
    unsigned int position;
} QueueNode;

// Define the structure of a queue
typedef struct Queue {
    QueueNode* data;
    int front, rear, capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (QueueNode*)malloc(capacity * sizeof(QueueNode));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front > queue->rear;
}

// Function to enqueue an element
void enqueue(Queue* queue, QueueNode item) {
    if (queue->rear + 1 < queue->capacity) {
        queue->data[++queue->rear] = item;
    }
}

// Function to dequeue an element
QueueNode dequeue(Queue* queue) {
    return queue->data[queue->front++];
}

// Function to find the maximum width of the binary tree
int getMaxWidth(TreeNode* root) {
    if (!root) return 0;

    // Initialize the queue
    Queue* queue = createQueue(1000);
    enqueue(queue, (QueueNode){root, 0});

    int maxWidth = 0;

    // Perform level-order traversal
    while (!isEmpty(queue)) {
        int levelSize = queue->rear - queue->front + 1;
        unsigned int start = queue->data[queue->front].position;
        unsigned int end = queue->data[queue->rear].position;

        // Update maximum width
        maxWidth = (end - start + 1 > maxWidth) ? (end - start + 1) : maxWidth;

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            QueueNode current = dequeue(queue);
            TreeNode* node = current.node;
            unsigned int position = current.position;

            // Add left child to the queue
            if (node->left) {
                enqueue(queue, (QueueNode){node->left, 2 * position + 1});
            }

            // Add right child to the queue
            if (node->right) {
                enqueue(queue, (QueueNode){node->right, 2 * position + 2});
            }
        }
    }

    // Free the queue memory
    free(queue->data);
    free(queue);

    return maxWidth;
}

// Helper function to create a new tree node
TreeNode* newNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Main function to test the solution
int main() {
    // Construct the binary tree
    TreeNode* root = newNode(1);
    root->left = newNode(3);
    root->right = newNode(2);
    root->left->left = newNode(5);
    root->left->right = newNode(3);
    root->right->right = newNode(9);

    // Find the maximum width
    int result = getMaxWidth(root);
    printf("Maximum width of the binary tree: %d\n", result);

    // Free allocated memory (not shown for simplicity)

    return 0;
}
