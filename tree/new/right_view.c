#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

int maxLevel = -1;

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

void printRightView(struct Node *node, int level) {
    // Base case: if the node is NULL, return
    if (node == NULL) return;

    // If this is the first time we are visiting this level, print the node's data
    if (level > maxLevel) {
        printf("%d ", node->data);
        maxLevel = level;
    }

    // First, go right (to get the rightmost node at each level)
    printRightView(node->right, level + 1);

    // Then go left (if necessary, although we prioritize right side)
    printRightView(node->left, level + 1);
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Right View of the Binary Tree: ");
    printRightView(root, 0);
    printf("\n");

    return 0;
}
