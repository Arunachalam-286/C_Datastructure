#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

// Function to insert a node in the binary tree
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

// Function to perform inorder traversal of the tree
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to find the LCA of two nodes
struct Node* LCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;

    // If root is one of n1 or n2, then root is LCA
    if (root->data == n1 || root->data == n2) return root;

    // Otherwise, check in left and right subtrees
    struct Node* leftLCA = LCA(root->left, n1, n2);
    struct Node* rightLCA = LCA(root->right, n1, n2);

    // If both left and right subtrees return non-null, this node is LCA
    if (leftLCA != NULL && rightLCA != NULL) return root;

    // Otherwise, check where the LCA is
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Function to find the distance from root to a given node
int findDistance(struct Node* root, int n, int distance) {
    if (root == NULL) return -1;  // If node is not found, return -1

    if (root->data == n) return distance;  // If node is found, return distance

    // Recursively find in left or right subtrees
    int leftDist = findDistance(root->left, n, distance + 1);
    if (leftDist != -1) return leftDist;

    return findDistance(root->right, n, distance + 1);  // Check in right subtree
}

// Function to calculate the distance between two nodes
int findDistanceBetweenNodes(struct Node* root, int n1, int n2) {
    // Find LCA of n1 and n2
    struct Node* lca = LCA(root, n1, n2);
    if (lca == NULL) return -1;  // If LCA doesn't exist, return -1

    // Find distance from LCA to n1 and n2
    int d1 = findDistance(lca, n1, 0);
    int d2 = findDistance(lca, n2, 0);

    if (d1 == -1 || d2 == -1) return -1;  // If either node is not found

    return d1 + d2;  // Distance between n1 and n2 is the sum of distances from LCA
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

    int n1, n2;
    printf("Enter two nodes to find the distance between them: ");
    scanf("%d %d", &n1, &n2);

    int distance = findDistanceBetweenNodes(root, n1, n2);
    if (distance == -1) {
        printf("One or both nodes not found in the tree.\n");
    } else {
        printf("The distance between nodes %d and %d is: %d\n", n1, n2, distance);
    }

    return 0;
}
