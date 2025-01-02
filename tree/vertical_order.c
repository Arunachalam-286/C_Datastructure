#include <stdio.h>
#include <stdlib.h>

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

// A structure to store a node and its horizontal distance (HD)
struct QueueNode {
    struct TreeNode* treeNode;
    int hd;
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

// Function to enqueue a node with its horizontal distance
void enqueue(struct Queue* queue, struct TreeNode* treeNode, int hd) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->hd = hd;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
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

// Node for a linked list to store values at the same horizontal distance
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to add a value to the linked list
void addToList(struct ListNode** head, int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the linked list
void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

// Function to print vertical order traversal
void verticalOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Hashmap to store nodes by horizontal distance
    struct ListNode* hashMap[1000] = {NULL};
    int offset = 500; // To handle negative HDs (array index can't be negative)
    int minHD = 500, maxHD = 500;

    // Queue for level-order traversal
    struct Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while (queue->front != NULL) {
        struct QueueNode* node = dequeue(queue);
        int hd = node->hd + offset;
        struct TreeNode* treeNode = node->treeNode;

        // Add the node value to the hashmap
        addToList(&hashMap[hd], treeNode->val);

        // Update min and max horizontal distances
        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        // Enqueue left and right children with updated HDs
        if (treeNode->left != NULL) {
            enqueue(queue, treeNode->left, node->hd - 1);
        }
        if (treeNode->right != NULL) {
            enqueue(queue, treeNode->right, node->hd + 1);
        }

        free(node); // Free the dequeued node
    }

    // Print the nodes grouped by horizontal distance
    for (int i = minHD; i <= maxHD; i++) {
        printList(hashMap[i]);
    }

    free(queue); // Free the queue
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("Vertical Order Traversal:\n");
    verticalOrderTraversal(root);

    return 0;
}
