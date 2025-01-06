#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

struct Node* createNode(int val) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct Node **node, int val) {
    if (*node == NULL) {
        *node = createNode(val);
        return;
    }

    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

void printVerticalUtil(struct Node *node, int hd, int verticalOrder[], int *index) {
    if (node == NULL) {
        return;
    }

    verticalOrder[hd + 100] = verticalOrder[hd + 100] + 1;
    index[0] = (index[0] > hd) ? hd : index[0];

    printVerticalUtil(node->left, hd - 1, verticalOrder, index);
    printVerticalUtil(node->right, hd + 1, verticalOrder, index);
}

void printVerticalOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    int verticalOrder[201] = {0};  // Array to store nodes of each vertical line.
    int index[1] = {0};  // To store the index of leftmost vertical distance.

    // Recursive helper function to fill the array and calculate the vertical distance.
    printVerticalUtil(root, 100, verticalOrder, index);

    // Print the vertical lines from leftmost to rightmost
    for (int i = index[0]; i <= 100; i++) {
        if (verticalOrder[i] != 0) {
            printf("%d ", verticalOrder[i]);
        }
    }

    printf("\n");
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

    printf("Vertical Order Traversal: ");
    printVerticalOrder(root);

    return 0;
}
