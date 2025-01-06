#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

void insert(struct Node **node, int val) {
    //1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    //2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Helper function to calculate the maximum path sum
int maxPathSumUtil(struct Node *node, int *res) {
    // Base case: If the node is NULL, return 0
    if (node == NULL) return 0;

    // Recursively calculate the maximum path sum for left and right subtrees
    int left = maxPathSumUtil(node->left, res);
    int right = maxPathSumUtil(node->right, res);

    // Calculate the maximum path sum for the current node
    int temp = max(node->data, node->data + max(left, right)); // Max single path (node to leaf)
    int ans = max(temp, node->data + left + right); // Max path through the current node
    *res = max(*res, ans); // Update the result if current path sum is greater

    return temp; // Return max path ending at this node
}

// Function to find the maximum path sum
int findMaxPathSum(struct Node *node) {
    int res = INT_MIN; // Initialize result to minimum integer value
    maxPathSumUtil(node, &res); // Calculate the maximum path sum
    return res;
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    int maxPathSum = findMaxPathSum(root);
    printf("Maximum Path Sum: %d\n", maxPathSum);

    return 0;
}
