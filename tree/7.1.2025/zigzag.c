#include<stdio.h>
#include<stdlib.h>

// Define the structure for a binary tree node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

// Insert a node into the binary tree
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

// Zigzag level order traversal using two stacks
void zigzagTraversal(struct Node *root) {
    if (root == NULL) return;

    // Two stacks for zigzag traversal
    struct Node *stack1[100]; // Stack for left-to-right traversal
    struct Node *stack2[100]; // Stack for right-to-left traversal
    int top1 = -1, top2 = -1;

    // Push the root to the first stack
    stack1[++top1] = root;

    printf("Zigzag Level Order Traversal: ");
    while (top1 != -1 || top2 != -1) {
        // Process nodes in stack1 (left-to-right)
        while (top1 != -1) {
            struct Node *current = stack1[top1--];
            printf("%d ", current->data);

            // Push left and right children to stack2
            if (current->left != NULL) {
                stack2[++top2] = current->left;
            }
            if (current->right != NULL) {
                stack2[++top2] = current->right;
            }
        }

        // Process nodes in stack2 (right-to-left)
        while (top2 != -1) {
            struct Node *current = stack2[top2--];
            printf("%d ", current->data);

            // Push right and left children to stack1
            if (current->right != NULL) {
                stack1[++top1] = current->right;
            }
            if (current->left != NULL) {
                stack1[++top1] = current->left;
            }
        }
    }
    printf("\n");
}

// Inorder traversal to verify the binary tree structure
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

    zigzagTraversal(root);

    return 0;
}
