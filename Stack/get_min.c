#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a structure for the stack
typedef struct Stack {
    int* data;       // Array to store stack elements
    int top;         // Index of the top element
    int capacity;    // Maximum capacity of the stack
    int currentMin;  // Current minimum element in the stack
} Stack;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    stack->currentMin = INT_MAX;
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

// Push operation
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    if (isEmpty(stack)) {
        stack->currentMin = value;
        stack->data[++stack->top] = value;
    } else {
        if (value < stack->currentMin) {
            // Store encoded value to keep track of the new minimum
            stack->data[++stack->top] = 2 * value - stack->currentMin;
            stack->currentMin = value;
        } else {
            stack->data[++stack->top] = value;
        }
    }

    printf("Pushed %d, Current Min: %d\n", value, stack->currentMin);
}

// Pop operation
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return INT_MIN;
    }

    int poppedValue = stack->data[stack->top--];
    if (poppedValue < stack->currentMin) {
        // Retrieve the previous minimum
        int originalMin = stack->currentMin;
        stack->currentMin = 2 * stack->currentMin - poppedValue;
        printf("Popped %d (was encoded), New Min: %d\n", originalMin, stack->currentMin);
        return originalMin;
    }

    printf("Popped %d, Current Min: %d\n", poppedValue, stack->currentMin);
    return poppedValue;
}

// Function to get the minimum element
int getMin(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    return stack->currentMin;
}

// Main function to demonstrate the stack
int main() {
    Stack* stack = createStack(10);

    push(stack, 10);
    push(stack, 20);
    printf("Current Min: %d\n", getMin(stack));

    push(stack, 5);
    printf("Current Min: %d\n", getMin(stack));

    pop(stack);
    printf("Current Min: %d\n", getMin(stack));

    pop(stack);
    printf("Current Min: %d\n", getMin(stack));

    return 0;
}
