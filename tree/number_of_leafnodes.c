#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Definition of a queue for level-order traversal
typedef struct Queue {
    TreeNode** data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (TreeNode**)malloc(capacity * sizeof(TreeNode*));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to enqueue a tree node
void enqueue(Queue* queue, TreeNode* node) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = node;
    queue->size++;
}

// Function to dequeue a tree node
TreeNode* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return NULL;
    TreeNode* node = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return node;
}

// Function to count the number of leaf nodes iteratively
int countLeafNodesIteratively(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    Queue* queue = createQueue(100); // Adjust the capacity as needed
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);

        // Check if the current node is a leaf node
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    free(queue->data);
    free(queue);

    return leafCount;
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

    // Count and print the number of leaf nodes in the binary tree
    int leafCount = countLeafNodesIteratively(root);
    printf("Number of leaf nodes in the binary tree (Iterative): %d\n", leafCount);

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
