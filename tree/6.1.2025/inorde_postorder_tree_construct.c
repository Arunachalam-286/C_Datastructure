#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

int postIndex = 0;  // To keep track of the current index in postorder

// Function to create a new node
struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find index of a given element in inorder
int searchInorder(int inorder[], int start, int end, int data) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == data) {
            return i;
        }
    }
    return -1;
}

// Function to build the tree from inorder and postorder traversals
struct Node* buildTree(int inorder[], int postorder[], int inorderStart, int inorderEnd) {
    // Base case
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // Get the current root from postorder traversal
    int rootData = postorder[postIndex];
    postIndex--;  // Decrease the postIndex for the next node

    struct Node *node = createNode(rootData);

    // If this node has no children, return it
    if (inorderStart == inorderEnd) {
        return node;
    }

    // Find the index of this node in inorder traversal
    int inorderIndex = searchInorder(inorder, inorderStart, inorderEnd, rootData);

    // Build the right subtree before the left subtree (because we are using postorder)
    node->right = buildTree(inorder, postorder, inorderIndex + 1, inorderEnd);
    node->left = buildTree(inorder, postorder, inorderStart, inorderIndex - 1);

    return node;
}

// Inorder Traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int n, val;

    // Read number of nodes
    scanf("%d", &n);

    int inorder[n], postorder[n];

    // Read inorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    // Read postorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }

    // Set postIndex to the last index of postorder
    postIndex = n - 1;

    // Build the tree from inorder and postorder traversals
    root = buildTree(inorder, postorder, 0, n - 1);

    // Print the inorder traversal of the constructed tree
    printf("Inorder Traversal of the constructed tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
