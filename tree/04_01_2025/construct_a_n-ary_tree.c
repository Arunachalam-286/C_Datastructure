#include<stdio.h>
#include<stdlib.h>

// Definition of an n-ary tree node
struct Node {
    int data;
    struct Node *child;
    struct Node *sibling;
}*root = NULL;

// Function to create a new node
struct Node* createNode(int val) {
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->child = NULL;
    newnode->sibling = NULL;
    return newnode;
}

// Function to insert a node into the n-ary tree
void insert(struct Node **node, int parentVal, int val) {
    if (*node == NULL) {
        *node = createNode(parentVal); // Create the root if it doesn't exist
    }
    struct Node *temp = *node;

    // Search for the parent node
    if (temp->data == parentVal) {
        // If the parent is found, add the new node as a child or sibling
        if (temp->child == NULL) {
            temp->child = createNode(val);
        } else {
            temp = temp->child;
            while (temp->sibling != NULL) {
                temp = temp->sibling;
            }
            temp->sibling = createNode(val);
        }
        return;
    }

    // Recursive search for the parent node in child and sibling
    if (temp->child != NULL) {
        insert(&(temp->child), parentVal, val);
    }
    if (temp->sibling != NULL) {
        insert(&(temp->sibling), parentVal, val);
    }
}

// Preorder traversal
void preorder(struct Node *node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->child);
    preorder(node->sibling);
}

// Postorder traversal
void postorder(struct Node *node) {
    if (node == NULL) return;
    postorder(node->child);
    printf("%d ", node->data);
    postorder(node->sibling);
}

int main() {
    int parent, child;
    printf("Enter parent-child pairs (parent -1 to stop):\n");
    while (1) {
        scanf("%d %d", &parent, &child);
        if (parent == -1)
            break;
        insert(&root, parent, child);
    }

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
