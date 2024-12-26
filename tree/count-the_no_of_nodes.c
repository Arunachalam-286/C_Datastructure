#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Utility function to create a new tree node
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Define the structure for a queue node
struct QueueNode {
    struct TreeNode* treeNode;
    struct QueueNode* next;
};

// Define the structure for a queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a tree node
void enqueue(struct Queue* queue, struct TreeNode* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a tree node
struct TreeNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    struct QueueNode* temp = queue->front;
    struct TreeNode* treeNode = temp->treeNode;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return treeNode;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to count the number of nodes at each level
void countNodesAtEachLevel(struct TreeNode* root) {
    if (root == NULL) {
        printf("The tree is empty.\n");
        return;
    }

    struct Queue* queue = createQueue();
    enqueue(queue, root);

    int level = 0;

    while (!isQueueEmpty(queue)) {
        int nodeCountAtCurrentLevel = 0;
        int size = 0;  // Number of nodes at the current level

        // Get the number of nodes at the current level
        struct QueueNode* current = queue->front;
        while (current != NULL) {
            size++;
            current = current->next;
        }

        // Process nodes at the current level
        while (size > 0) {
            struct TreeNode* currentNode = dequeue(queue);
            nodeCountAtCurrentLevel++;

            // Enqueue left and right children of the current node, if they exist
            if (currentNode->left != NULL) {
                enqueue(queue, currentNode->left);
            }
            if (currentNode->right != NULL) {
                enqueue(queue, currentNode->right);
            }
            size--;
        }

        // Print the number of nodes at the current level
        printf("Level %d: %d nodes\n", level, nodeCountAtCurrentLevel);
        level++;
    }
}

int main() {
    // Example usage
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Count nodes at each level
    countNodesAtEachLevel(root);

    // Free allocated memory (not shown for simplicity)
    return 0;
}
