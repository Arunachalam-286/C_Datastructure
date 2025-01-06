#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

int preIndex = 0;

// Function to create a new node
struct Node* createNode(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to search for a value in the inorder array
int searchInInorder(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to build the tree from preorder and inorder traversals
struct Node* buildTree(int inorder[], int preorder[], int inorderStart, int inorderEnd) {
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // Get the root node from the preorder array
    int rootValue = preorder[preIndex++];
    struct Node* node = createNode(rootValue);

    // If the node has no children (leaf node), return
    if (inorderStart == inorderEnd) {
        return node;
    }

    // Find the index of the root in inorder traversal
    int inorderIndex = searchInInorder(inorder, inorderStart, inorderEnd, rootValue);

    // Recursively build the left and right subtrees
    node->left = buildTree(inorder, preorder, inorderStart, inorderIndex - 1);
    node->right = buildTree(inorder, preorder, inorderIndex + 1, inorderEnd);

    return node;
}

// Function to do inorder traversal of the tree
void inorderTraversal(struct Node* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int main() {
    int n, i;
    
    // Read number of elements in the tree
    scanf("%d", &n);

    int inorder[n], preorder[n];
    
    // Read inorder and preorder traversals
    printf("Enter the inorder traversal: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    printf("Enter the preorder traversal: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    
    // Build the tree using inorder and preorder
    root = buildTree(inorder, preorder, 0, n - 1);

    // Print inorder traversal of the constructed tree
    printf("Inorder Traversal of Constructed Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
