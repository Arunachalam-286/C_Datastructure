#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

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

// Function to calculate the sum of all nodes at the k-th level
int sumAtLevel(struct Node *node, int currentLevel, int k) {
    if (node == NULL) return 0;

    if (currentLevel == k) {
        return node->data; // If the current level matches k, include the node's value
    }

    // Recursively sum the values from left and right subtrees
    return sumAtLevel(node->left, currentLevel + 1, k) + 
           sumAtLevel(node->right, currentLevel + 1, k);
}

int main() {
    int val, k;
    
    // Insert nodes into the binary tree
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Input the level (k) for which the sum is to be calculated
    printf("Enter the level (k): ");
    scanf("%d", &k);

    // Calculate and print the sum of nodes at level k
    int sum = sumAtLevel(root, 0, k);
    printf("Sum of nodes at level %d: %d\n", k, sum);

    return 0;
}
