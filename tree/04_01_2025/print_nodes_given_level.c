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

// Function to find the height of the tree
int height(struct Node *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to print all nodes at a given level
void printGivenLevel(struct Node *node, int level) {
    if (node == NULL) return;
    if (level == 1) {
        printf("%d ", node->data);
    } else if (level > 1) {
        printGivenLevel(node->left, level - 1);
        printGivenLevel(node->right, level - 1);
    }
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

    int level;
    printf("Enter the level to print nodes: ");
    scanf("%d", &level);

    printf("Nodes at level %d: ", level);
    printGivenLevel(root, level);
    printf("\n");

    return 0;
}
