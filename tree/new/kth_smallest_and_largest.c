#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Insert a node into the BST
void insert(struct Node **node, int val) {
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Helper function to find kth smallest element
void findKthSmallest(struct Node *node, int *k, int *result) {
    if (node == NULL || *k <= 0) return;

    findKthSmallest(node->left, k, result);

    (*k)--;
    if (*k == 0) {
        *result = node->data;
        return;
    }

    findKthSmallest(node->right, k, result);
}

// Helper function to find kth largest element
void findKthLargest(struct Node *node, int *k, int *result) {
    if (node == NULL || *k <= 0) return;

    findKthLargest(node->right, k, result);

    (*k)--;
    if (*k == 0) {
        *result = node->data;
        return;
    }

    findKthLargest(node->left, k, result);
}

// Perform inorder traversal of the BST
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val, k, result;

    // Insert elements into the BST
    printf("Enter values to insert into the BST (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Display the BST in inorder
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Find kth smallest element
    printf("Enter k to find the kth smallest element: ");
    scanf("%d", &k);
    result = -1;
    findKthSmallest(root, &k, &result);
    if (result != -1) {
        printf("The %dth smallest element is: %d\n", k, result);
    } else {
        printf("The %dth smallest element does not exist.\n", k);
    }

    // Find kth largest element
    printf("Enter k to find the kth largest element: ");
    scanf("%d", &k);
    result = -1;
    findKthLargest(root, &k, &result);
    if (result != -1) {
        printf("The %dth largest element is: %d\n", k, result);
    } else {
        printf("The %dth largest element does not exist.\n", k);
    }

    return 0;
}
