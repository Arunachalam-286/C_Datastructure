#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure for main stack
struct Stack {
    int data[MAX];
    int top;
};

// Stack structure for min stack
struct MinStack {
    struct Stack mainStack;
    struct Stack minStack;
};

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to initialize the min stack
void initMinStack(struct MinStack* minStack) {
    initStack(&minStack->mainStack);
    initStack(&minStack->minStack);
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Function to push an element onto the main stack and update the min stack
void push(struct MinStack* minStack, int value) {
    if (isFull(&minStack->mainStack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    minStack->mainStack.data[++minStack->mainStack.top] = value;

    // Push to min stack if it is empty or the value is less than or equal to the current minimum
    if (isEmpty(&minStack->minStack) || value <= minStack->minStack.data[minStack->minStack.top]) {
        minStack->minStack.data[++minStack->minStack.top] = value;
    }
}

// Function to pop an element from the main stack and update the min stack
int pop(struct MinStack* minStack) {
    if (isEmpty(&minStack->mainStack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    int poppedValue = minStack->mainStack.data[minStack->mainStack.top--];

    // Pop from min stack if the popped value is the current minimum
    if (poppedValue == minStack->minStack.data[minStack->minStack.top]) {
        minStack->minStack.top--;
    }

    return poppedValue;
}

// Function to get the minimum element
int getMin(struct MinStack* minStack) {
    if (isEmpty(&minStack->minStack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return minStack->minStack.data[minStack->minStack.top];
}

int main() {
    struct MinStack minStack;
    initMinStack(&minStack);

    push(&minStack, 5);
    push(&minStack, 3);
    push(&minStack, 7);
    printf("Minimum: %d\n", getMin(&minStack)); // Output: 3

    pop(&minStack);
    printf("Minimum: %d\n", getMin(&minStack)); // Output: 3

    pop(&minStack);
    printf("Minimum: %d\n", getMin(&minStack)); // Output: 5

    return 0;
}
