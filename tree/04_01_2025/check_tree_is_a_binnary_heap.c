#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

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

// Check if the tree satisfies the heap property
bool isHeapProperty(struct Node *node) {
    if (node == NULL)
        return true;

    // Check if node's data is greater than its children (max-heap condition)
    if ((node->left && node->data < node->left->data) ||
        (node->right && node->data < node->right->data)) {
        return false;
    }

    // Recursively check for left and right subtrees
    return isHeapProperty(node->left) && isHeapProperty(node->right);
}

// Check if the tree is complete
bool isCompleteTree(struct Node *node) {
    if (node == NULL)
        return true;

    struct Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = node;
    bool flag = false;

    while (front < rear) {
        struct Node *temp = queue[front++];
        
        if (temp->left) {
            if (flag) // If a non-full node was seen earlier, return false
                return false;
            queue[rear++] = temp->left;
        } else {
            flag = true; // Mark the first non-full node
        }

        if (temp->right) {
            if (flag) // If a non-full node was seen earlier, return false
                return false;
            queue[rear++] = temp->right;
        } else {
            flag = true; // Mark the first non-full node
        }
    }
    return true;
}

bool isBinaryHeap(struct Node *root) {
    return isCompleteTree(root) && isHeapProperty(root);
}

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

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    if (isBinaryHeap(root)) {
        printf("The tree is a Binary Heap.\n");
    } else {
        printf("The tree is NOT a Binary Heap.\n");
    }

    return 0;
}
