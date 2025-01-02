#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Definition of a queue node
struct QueueNode {
    struct TreeNode *treeNode;
    struct QueueNode *next;
};

// Definition of a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a new queue node
struct QueueNode* createQueueNode(struct TreeNode* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a tree node
void enqueue(struct Queue* queue, struct TreeNode* treeNode) {
    struct QueueNode* newNode = createQueueNode(treeNode);
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
bool isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to perform zigzag level order traversal
void zigzagLevelOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct Queue* queue = createQueue();
    enqueue(queue, root);
    bool leftToRight = true;

    while (!isQueueEmpty(queue)) {
        int size = 0;
        struct QueueNode* current = queue->front;
        while (current != NULL) {
            size++;
            current = current->next;
        }

        int* level = (int*)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            struct TreeNode* node = dequeue(queue);
            int index = leftToRight ? i : size - 1 - i;
            level[index] = node->val;

            if (node->left) {
                enqueue(queue, node->left);
            }
            if (node->right) {
                enqueue(queue, node->right);
            }
        }

        // Print the current level
        for (int i = 0; i < size; i++) {
            printf("%d ", level[i]);
        }
        printf("\n");

        free(level);
        leftToRight = !leftToRight;
    }
}

// Main function to test the zigzag level order traversal
int main() {
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("Zigzag Level Order Traversal:\n");
    zigzagLevelOrder(root);

    return 0;
}
