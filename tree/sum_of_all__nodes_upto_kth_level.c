#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find the sum of nodes at the kth level
int sumAtKthLevel(struct Node* root, int k) {
    if (root == NULL)
        return 0;

    // Queue for level order traversal
    struct Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int currentLevel = 0;
    int sum = 0;

    while (front < rear) {
        int levelSize = rear - front; // Number of nodes at the current level
        sum = 0; // Reset sum for each level

        for (int i = 0; i < levelSize; i++) {
            struct Node* current = queue[front++];

            // If we are at the kth level, sum up the node values
            if (currentLevel == k) {
                sum += current->data;
            }

            // Add children to the queue
            if (current->left)
                queue[rear++] = current->left;
            if (current->right)
                queue[rear++] = current->right;
        }

        // If we have reached the kth level, return the sum
        if (currentLevel == k)
            return sum;

        currentLevel++;
    }

    // If k is greater than the height of the tree
    return 0;
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

    int k = 2;
    printf("Sum of nodes at level %d: %d\n", k, sumAtKthLevel(root, k));

    return 0;
}
