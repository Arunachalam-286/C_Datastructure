#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

void insert(struct Node **node, int val) {
    // If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    // Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// Function to flatten the binary tree to a linked list
void flatten(struct Node *root) {
    if (root == NULL) return;
    
    // If there's a left child, we need to handle it
    if (root->left != NULL) {
        // Recursively flatten the left subtree
        flatten(root->left);

        // Store the current right subtree
        struct Node *tempRight = root->right;

        // Move the left subtree to the right
        root->right = root->left;
        root->left = NULL;

        // Find the last node of the new right subtree (which was the left subtree)
        struct Node *temp = root->right;
        while (temp->right != NULL) {
            temp = temp->right;
        }

        // Connect the original right subtree to the end of the new right subtree
        temp->right = tempRight;
    }

    // Recursively flatten the right subtree
    flatten(root->right);
}

// Function to print the flattened tree (linked list)
void printFlattened(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->right; // Move to the next node in the flattened structure
    }
    printf("\n");
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Flatten the binary tree to a linked list
    flatten(root);

    // Print the flattened tree (linked list)
    printf("Flattened tree (linked list): ");
    printFlattened(root);
    printf("\n");

    return 0;
}
