#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

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

// Function to check if two trees are identical
bool areIdentical(struct Node *root1, struct Node *root2) {
    // If both trees are empty, they are identical
    if (root1 == NULL && root2 == NULL)
        return true;
    // If one tree is empty and the other is not, they are not identical
    if (root1 == NULL || root2 == NULL)
        return false;
    // If the data of the current nodes is the same, check recursively for left and right subtrees
    return (root1->data == root2->data) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

// Function to check if a tree T2 is a subtree of tree T1
bool isSubtree(struct Node *T1, struct Node *T2) {
    // If T2 is NULL, it is always a subtree (empty tree is always a subtree)
    if (T2 == NULL)
        return true;
    // If T1 is NULL, T2 cannot be a subtree of T1
    if (T1 == NULL)
        return false;
    // If the current nodes of T1 and T2 are identical, check if they are identical
    if (areIdentical(T1, T2))
        return true;
    // Otherwise, recursively check for the subtree in the left and right subtrees of T1
    return isSubtree(T1->left, T2) || isSubtree(T1->right, T2);
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int val;
    struct Node *root2 = NULL;  // Second tree (potential subtree)
    
    // Construct the first tree (T1)
    printf("Enter values for the first tree (T1), -1 to stop:\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Construct the second tree (T2)
    printf("Enter values for the second tree (T2), -1 to stop:\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root2, val);
    } while (val != -1);

    // Check if T2 is a subtree of T1
    if (isSubtree(root, root2)) {
        printf("T2 is a subtree of T1.\n");
    } else {
        printf("T2 is NOT a subtree of T1.\n");
    }

    printf("Inorder Traversal of T1: ");
    inorder(root);
    printf("\n");

    printf("Inorder Traversal of T2: ");
    inorder(root2);
    printf("\n");

    return 0;
}
