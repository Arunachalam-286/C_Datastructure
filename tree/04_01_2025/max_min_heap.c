#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Create a new node
struct Node* createNode(int val) {
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Insert nodes in level order to maintain completeness
void insertLevelOrder(struct Node **node, int val) {
    struct Node *newnode = createNode(val);
    if (*node == NULL) {
        *node = newnode;
        return;
    }

    struct Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = *node;

    while (front < rear) {
        struct Node *temp = queue[front++];
        if (temp->left == NULL) {
            temp->left = newnode;
            return;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newnode;
            return;
        } else {
            queue[rear++] = temp->right;
        }
    }
}

// In-order traversal to collect node values
void storeInOrder(struct Node *node, int arr[], int *index) {
    if (node == NULL) return;
    storeInOrder(node->left, arr, index);
    arr[(*index)++] = node->data;
    storeInOrder(node->right, arr, index);
}

// Build a heap-ordered tree from array
void buildHeapTree(struct Node *node, int arr[], int *index) {
    if (node == NULL) return;
    node->data = arr[(*index)++];
    buildHeapTree(node->left, arr, index);
    buildHeapTree(node->right, arr, index);
}

// Convert binary tree to max or min heap
void convertToHeap(struct Node *node, int isMaxHeap) {
    if (node == NULL) return;

    int arr[100], n = 0, i;
    storeInOrder(node, arr, &n);

    // Sort array for heap order
    if (isMaxHeap) {
        // Sort in descending order for max heap
        for (i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    } else {
        // Sort in ascending order for min heap
        for (i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Rebuild tree in heap order
    int index = 0;
    buildHeapTree(node, arr, &index);
}

// In-order traversal for display
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val;
    printf("Enter values to construct the tree (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insertLevelOrder(&root, val);
    } while (val != -1);

    printf("Inorder Traversal (Original Tree): ");
    inorder(root);
    printf("\n");

    int choice;
    printf("Convert to:\n1. Max Heap\n2. Min Heap\nEnter choice: ");
    scanf("%d", &choice);

    convertToHeap(root, choice == 1);

    printf("Inorder Traversal (Heap Ordered Tree): ");
    inorder(root);
    printf("\n");

    return 0;
}
