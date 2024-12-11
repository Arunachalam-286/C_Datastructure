#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure for main stack
struct Stack {
    int data[MAX];
    int top;
};

// Stack structure for max stack
struct MaxStack {
    struct Stack mainStack;
    struct Stack maxStack;
};

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to initialize the max stack
void initMaxStack(struct MaxStack* maxStack) {
    initStack(&maxStack->mainStack);
    initStack(&maxStack->maxStack);
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Function to push an element onto the main stack and update the max stack
void push(struct MaxStack* maxStack, int value) {
    if (isFull(&maxStack->mainStack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    maxStack->mainStack.data[++maxStack->mainStack.top] = value;

    // Push to max stack if it is empty or the value is greater than or equal to the current maximum
    if (isEmpty(&maxStack->maxStack) || value >= maxStack->maxStack.data[maxStack->maxStack.top]) {
        maxStack->maxStack.data[++maxStack->maxStack.top] = value;
    }
}

// Function to pop an element from the main stack and update the max stack
int pop(struct MaxStack* maxStack) {
    if (isEmpty(&maxStack->mainStack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    int poppedValue = maxStack->mainStack.data[maxStack->mainStack.top--];

    // Pop from max stack if the popped value is the current maximum
    if (poppedValue == maxStack->maxStack.data[maxStack->maxStack.top]) {
        maxStack->maxStack.top--;
    }

    return poppedValue;
}

// Function to get the maximum element
int getMax(struct MaxStack* maxStack) {
    if (isEmpty(&maxStack->maxStack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return maxStack->maxStack.data[maxStack->maxStack.top];
}

int main() {
    struct MaxStack maxStack;
    initMaxStack(&maxStack);

    push(&maxStack, 5);
    push(&maxStack, 3);
    push(&maxStack, 7);
    printf("Maximum: %d\n", getMax(&maxStack)); // Output: 7

    pop(&maxStack);
    printf("Maximum: %d\n", getMax(&maxStack)); // Output: 5

    pop(&maxStack);
    printf("Maximum: %d\n", getMax(&maxStack)); // Output: 5

    return 0;
}
