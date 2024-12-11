#include <stdio.h>
#include <stdlib.h>

// Define a node for the linked list
typedef struct Node {
    int data;           // Data field to store the value
    struct Node* next;  // Pointer to the next node
} Node;

// Define the stack structure
typedef struct Stack {
    Node* top;  // Pointer to the top element of the stack
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;  // Stack is initially empty
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed! Cannot push %d\n", value);
        return;
    }
    newNode->data = value;
    newNode->next = stack->top;  // Link the new node to the current top
    stack->top = newNode;        // Update the top to the new node
    printf("Pushed %d onto the stack\n", value);
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop\n");
        return -1;  // Return -1 to indicate underflow
    }
    Node* temp = stack->top;    // Store the top node
    int poppedValue = temp->data; // Get the data from the top node
    stack->top = stack->top->next; // Update the top to the next node
    free(temp);                 // Free the old top node
    return poppedValue;
}

// Function to peek at the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Cannot peek\n");
        return -1;  // Return -1 to indicate the stack is empty
    }
    return stack->top->data;
}

// Function to free the stack memory
void freeStack(Stack* stack) {
    Node* current = stack->top;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
}

// Main function to demonstrate stack operations
int main() {
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(&stack));

    printf("Popped %d from the stack\n", pop(&stack));
    printf("Popped %d from the stack\n", pop(&stack));
    printf("Popped %d from the stack\n", pop(&stack));

    if (isEmpty(&stack)) {
        printf("Stack is empty\n");
    }

    freeStack(&stack);  // Clean up memory
    return 0;
}