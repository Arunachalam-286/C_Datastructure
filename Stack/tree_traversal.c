#include <stdio.h>
#include <stdlib.h>

// Define a binary tree node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Define a stack structure
typedef struct Stack {
    Node** data;
    int top;
    int capacity;
} Stack;

// Create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (Node**)malloc(capacity * sizeof(Node*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push an element onto the stack
void push(Stack* stack, Node* node) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->data[++stack->top] = node;
}

// Pop an element from the stack
Node* pop(Stack* stack) {
    if (stack->top == -1) {
        return NULL;
    }
    return stack->data[stack->top--];
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Preorder traversal (root -> left -> right) using a stack
void preorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        Node* current = pop(stack);
        printf("%d ", current->data);

        // Push right child first so left child is processed first
        if (current->right) push(stack, current->right);
        if (current->left) push(stack, current->left);
    }

    freeStack(stack);
}

// Inorder traversal (left -> root -> right) using a stack
void inorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack = createStack(100);
    Node* current = root;

    while (!isEmpty(stack) || current != NULL) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        // Current must be NULL at this point
        current = pop(stack);
        printf("%d ", current->data);

        // Visit the right subtree
        current = current->right;
    }

    freeStack(stack);
}

// Postorder traversal (left -> right -> root) using a stack
void postorderTraversal(Node* root) {
    if (!root) return;

    Stack* stack1 = createStack(100);
    Stack* stack2 = createStack(100);

    push(stack1, root);

    // Push nodes into the first stack and process them into the second stack
    while (!isEmpty(stack1)) {
        Node* current = pop(stack1);
        push(stack2, current);

        if (current->left) push(stack1, current->left);
        if (current->right) push(stack1, current->right);
    }

    // Pop all nodes from the second stack to get postorder traversal
    while (!isEmpty(stack2)) {
        printf("%d ", pop(stack2)->data);
    }

    freeStack(stack1);
    freeStack(stack2);
}

// Main function to demonstrate the traversals
int main() {
    // Example tree:
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7

    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
