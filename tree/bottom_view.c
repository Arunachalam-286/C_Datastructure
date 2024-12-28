#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure to represent a queue node for level order traversal
struct QueueNode {
    struct Node* treeNode;
    int hd; // horizontal distance
    struct QueueNode* next;
};

// Queue for level order traversal
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Enqueue a tree node with its horizontal distance
void enqueue(struct Queue* queue, struct Node* treeNode, int hd) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = treeNode;
    temp->hd = hd;
    temp->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

// Dequeue a tree node and its horizontal distance
struct QueueNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return NULL;

    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    return temp;
}

// Function to print the bottom view of the binary tree
void printBottomView(struct Node* root) {
    if (root == NULL)
        return;

    // Create a queue for level order traversal
    struct Queue* queue = createQueue();

    // Map to store the bottommost nodes at each horizontal distance
    int minHD = 0, maxHD = 0;
    int bottomView[1000] = {0}; // Adjust size for a larger tree

    // Enqueue the root node with horizontal distance 0
    enqueue(queue, root, 0);

    while (queue->front != NULL) {
        struct QueueNode* temp = dequeue(queue);

        struct Node* current = temp->treeNode;
        int hd = temp->hd;

        // Update the map with the current node for the horizontal distance
        bottomView[hd + 500] = current->data;

        if (hd < minHD)
            minHD = hd;
        if (hd > maxHD)
            maxHD = hd;

        // Enqueue the left and right children of the current node
        if (current->left)
            enqueue(queue, current->left, hd - 1);
        if (current->right)
            enqueue(queue, current->right, hd + 1);

        free(temp);
    }

    // Print the bottom view
    for (int i = minHD + 500; i <= maxHD + 500; i++) {
        printf("%d ", bottomView[i]);
    }
    printf("\n");

    free(queue);
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

    printf("Bottom View of the Binary Tree: ");
    printBottomView(root);

    return 0;
}
