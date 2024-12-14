#include <stdio.h>
#include <stdlib.h>

// Define the stack structure
typedef struct {
    int* data;    // Array to hold stack elements
    int top;      // Index of the top element
    int capacity; // Maximum capacity of the stack
} Stack;

// Function to create a new stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
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
        printf("Stack overflow!\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// Function to get the top element of the stack
int top(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->data[stack->top];
}

// Function to perform a multi-pop operation
void multiPop(Stack* stack, int k) {
    if (k <= 0) {
        printf("Invalid number of elements to pop.\n");
        return;
    }
    int pops = (k > stack->top + 1) ? stack->top + 1 : k; // Limit pops to available elements
    stack->top -= pops;
    printf("Popped %d elements.\n", pops);
}

// Function to display the stack elements
void display(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

// Main function to demonstrate the stack
int main() {
    int capacity = 10;
    Stack* stack = createStack(capacity);

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);

    printf("Initial stack:\n");
    display(stack);

    printf("\nPerforming multiPop(2):\n");
    multiPop(stack, 2);
    display(stack);

    printf("\nPerforming multiPop(5):\n");
    multiPop(stack, 5);
    display(stack);

    // Free memory
    free(stack->data);
    free(stack);

    return 0;
}
