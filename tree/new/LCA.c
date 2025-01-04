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

// Function to find the LCA of two nodes
struct Node* findLCA(struct Node* root, int n1, int n2) {
    // Base case: if root is NULL, return NULL
    if (root == NULL)
        return NULL;

    // If either n1 or n2 matches the root's data, return root
    if (root->data == n1 || root->data == n2)
        return root;

    // Recur for left and right subtrees
    struct Node* leftLCA = findLCA(root->left, n1, n2);
    struct Node* rightLCA = findLCA(root->right, n1, n2);

    // If both left and right LCA are non-NULL, the current node is the LCA
    if (leftLCA != NULL && rightLCA != NULL)
        return root;

    // Otherwise, return the non-NULL child
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
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
    printf("Enter two nodes to find their LCA: ");
    scanf("%d %d", &n1, &n2);

    struct Node* lca = findLCA(root, n1, n2);
    if (lca != NULL)
        printf("LCA of %d and %d is %d\n", n1, n2, lca->data);
    else
        printf("LCA not found.\n");

    return 0;
}
