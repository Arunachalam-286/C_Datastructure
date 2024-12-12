#include <stdio.h>
#include <stdlib.h>

// Stack structure
typedef struct {
    int* stack;       // Array to store stack elements
    int* increment;   // Auxiliary array for increment tracking
    int top;          // Index of the top element
    int capacity;     // Maximum capacity of the stack
} CustomStack;

// Create a stack with a given maximum capacity
CustomStack* createStack(int capacity) {
    CustomStack* stack = (CustomStack*)malloc(sizeof(CustomStack));
    stack->stack = (int*)malloc(capacity * sizeof(int));
    stack->increment = (int*)calloc(capacity, sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push an element onto the stack
void push(CustomStack* stack, int x) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->stack[++stack->top] = x;
    printf("Pushed %d onto the stack.\n", x);
}

// Pop an element from the stack
int pop(CustomStack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow.\n");
        return -1;
    }

    int idx = stack->top;
    int value = stack->stack[idx] + stack->increment[idx];

    // Propagate the increment to the next element
    if (idx > 0) {
        stack->increment[idx - 1] += stack->increment[idx];
    }

    stack->increment[idx] = 0;  // Clear the increment for this index
    stack->top--;
    printf("Popped %d from the stack.\n", value);
    return value;
}

// Increment the bottom k elements by a given value
void increment(CustomStack* stack, int k, int val) {
    if (stack->top == -1) {
        printf("Stack is empty. Increment operation skipped.\n");
        return;
    }
    int limit = (k > stack->top + 1) ? stack->top + 1 : k;
    stack->increment[limit - 1] += val;
    printf("Incremented bottom %d elements by %d.\n", k, val);
}

// Print the stack
void printStack(CustomStack* stack) {
    printf("Stack elements: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->stack[i] + stack->increment[i]);
    }
    printf("\n");
}

// Free the stack
void freeStack(CustomStack* stack) {
    free(stack->stack);
    free(stack->increment);
    free(stack);
}

// Main function to demonstrate functionality
int main() {
    CustomStack* stack = createStack(5);

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    printStack(stack);

    increment(stack, 2, 10);
    printStack(stack);

    pop(stack);
    printStack(stack);

    increment(stack, 3, 5);
    printStack(stack);

    pop(stack);
    pop(stack);
    pop(stack);

    freeStack(stack);
    return 0;
}
