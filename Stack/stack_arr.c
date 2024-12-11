#include <stdio.h>
#include <stdlib.h>

// Define a stack structure
typedef struct Stack {
    int* arr;  // Pointer to dynamically allocate memory for the stack
    int top;   // Index of the top element
    int capacity; // Maximum size of the stack
} Stack;

// Function to create a stack with a given capacity
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Pushed %d onto the stack\n", value);
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop\n");
        return -1;  // Return -1 to indicate underflow
    }
    return stack->arr[stack->top--];
}

// Function to peek at the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Cannot peek\n");
        return -1;  // Return -1 to indicate the stack is empty
    }
    return stack->arr[stack->top];
}

// Function to free the stack memory
void freeStack(Stack* stack) {
    free(stack->arr);
    free(stack);
}

// Main function to demonstrate stack operations
int main() {
    int capacity = 5;  // Define the capacity of the stack
    Stack* stack = createStack(capacity);

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Top element is %d\n", peek(stack));

    printf("Popped %d from the stack\n", pop(stack));
    printf("Popped %d from the stack\n", pop(stack));
    printf("Popped %d from the stack\n", pop(stack));

    if (isEmpty(stack)) {
        printf("Stack is empty\n");
    }

    freeStack(stack);  // Clean up memory
    return 0;
}