#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to find the LCA (Lowest Common Ancestor) of two nodes in a binary tree
struct TreeNode* findLCA(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }

    struct TreeNode* left = findLCA(root->left, p, q);
    struct TreeNode* right = findLCA(root->right, p, q);

    if (left != NULL && right != NULL) {
        return root;  // If p and q are found in both subtrees, root is their LCA
    }

    return (left != NULL) ? left : right;  // Otherwise, return the non-null node
}

// Function to find the distance from the root to a given node
int findDistance(struct TreeNode* root, struct TreeNode* target, int distance) {
    if (root == NULL) {
        return -1;  // Return -1 if the node is not found
    }

    if (root == target) {
        return distance;  // Return the current distance if the node is found
    }

    // Recur for left and right subtrees
    int leftDist = findDistance(root->left, target, distance + 1);
    int rightDist = findDistance(root->right, target, distance + 1);

    // If the node is found in either left or right subtree, return the distance
    return (leftDist != -1) ? leftDist : rightDist;
}

// Function to find the distance between two nodes in a binary tree
int findDistanceBetweenNodes(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    // Step 1: Find the LCA of p and q
    struct TreeNode* lca = findLCA(root, p, q);

    // Step 2: Find the distance from LCA to p and LCA to q
    int distanceP = findDistance(lca, p, 0);
    int distanceQ = findDistance(lca, q, 0);

    // The distance between p and q is the sum of the distances from LCA to p and LCA to q
    return distanceP + distanceQ;
}

// Main function to test the implementation
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->right = createTreeNode(6);

    // Find the distance between nodes 4 and 5
    struct TreeNode* p = root->left->left;  // Node 4
    struct TreeNode* q = root->left->right; // Node 5
    int distance = findDistanceBetweenNodes(root, p, q);
    printf("Distance between nodes %d and %d is: %d\n", p->val, q->val, distance);

    // Find the distance between nodes 4 and 6
    q = root->right->right; // Node 6
    distance = findDistanceBetweenNodes(root, p, q);
    printf("Distance between nodes %d and %d is: %d\n", p->val, q->val, distance);

    return 0;
}
