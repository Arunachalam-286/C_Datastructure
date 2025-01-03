#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* buildTree() {
    int val;
    printf("Enter node value (-1 for NULL): ");
    scanf("%d", &val);

    if (val == -1) {
        return NULL; // Null node
    }

    TreeNode* root = createNode(val);
    printf("Enter left child of %d\n", val);
    root->left = buildTree();

    printf("Enter right child of %d\n", val);
    root->right = buildTree();

    return root;
}

// Inorder traversal (Left, Root, Right)
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

// Preorder traversal (Root, Left, Right)
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder traversal (Left, Right, Root)
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->val);
}

// Main function to test the implementation
int main() {
    printf("Build the binary tree:\n");
    TreeNode* root = buildTree();

    // Perform tree traversals
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}