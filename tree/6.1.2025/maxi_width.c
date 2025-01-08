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

// Helper function to count nodes at a given level
int countNodesAtLevel(struct Node *node, int level) {
    if (node == NULL) {
        return 0;
    }
    if (level == 1) {
        return 1;
    } else {
        return countNodesAtLevel(node->left, level - 1) + countNodesAtLevel(node->right, level - 1);
    }
}

// Function to calculate the maximum width of the tree
int maxWidth(struct Node *node) {
    int height = getHeight(node);
    int max_width = 0;
    
    for (int level = 1; level <= height; level++) {
        int width_at_level = countNodesAtLevel(node, level);
        if (width_at_level > max_width) {
            max_width = width_at_level;
        }
    }
    
    return max_width;
}

// Helper function to calculate the height of the tree
int getHeight(struct Node *node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Inorder traversal to display the tree
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

    printf("Maximum Width of the Binary Tree: %d\n", maxWidth(root));

    return 0;
}
