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

// A node for the queue with diagonal level information
struct QueueNode {
    struct TreeNode* treeNode;
    int diagonal;
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

// Function to enqueue a node with its diagonal level
void enqueue(struct Queue* queue, struct TreeNode* treeNode, int diagonal) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->diagonal = diagonal;
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

// A node for a linked list to store values of each diagonal
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

// Function to perform diagonal traversal
void diagonalTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Hashmap to store nodes by diagonal level
    struct ListNode* hashMap[1000] = {NULL};
    int maxDiagonal = 0;

    // Queue for level-order traversal
    struct Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while (queue->front != NULL) {
        struct QueueNode* node = dequeue(queue);
        int diagonal = node->diagonal;
        struct TreeNode* treeNode = node->treeNode;

        // Add the node value to the hashmap
        addToList(&hashMap[diagonal], treeNode->val);

        // Update max diagonal level
        if (diagonal > maxDiagonal) {
            maxDiagonal = diagonal;
        }

        // Enqueue left child to the next diagonal level
        if (treeNode->left != NULL) {
            enqueue(queue, treeNode->left, diagonal + 1);
        }

        // Enqueue right child to the same diagonal level
        if (treeNode->right != NULL) {
            enqueue(queue, treeNode->right, diagonal);
        }

        free(node); // Free the dequeued node
    }

    // Print the diagonals
    for (int i = 0; i <= maxDiagonal; i++) {
        printList(hashMap[i]);
    }

    free(queue); // Free the queue
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(8);
    root->left = createTreeNode(3);
    root->right = createTreeNode(10);
    root->left->left = createTreeNode(1);
    root->left->right = createTreeNode(6);
    root->right->right = createTreeNode(14);
    root->right->right->left = createTreeNode(13);
    root->left->right->left = createTreeNode(4);
    root->left->right->right = createTreeNode(7);

    printf("Diagonal Traversal:\n");
    diagonalTraversal(root);

    return 0;
}
