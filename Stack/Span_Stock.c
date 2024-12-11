#include <stdio.h>
#include <stdlib.h>

// Structure for a stack
typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

// Function to create a stack
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

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    stack->data[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->data[stack->top--];
}

// Function to get the top element of the stack
int top(Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->data[stack->top];
}

// Function to calculate stock spans
void calculateSpan(int prices[], int n, int span[]) {
    Stack* stack = createStack(n);

    for (int i = 0; i < n; i++) {
        // Pop elements from the stack while the current price is greater than the price at stack.top
        while (!isEmpty(stack) && prices[top(stack)] <= prices[i]) {
            pop(stack);
        }

        // Calculate span
        if (isEmpty(stack)) {
            span[i] = i + 1;
        } else {
            span[i] = i - top(stack);
        }

        // Push current index onto the stack
        push(stack, i);
    }

    free(stack->data);
    free(stack);
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int prices[] = {100, 80, 60, 70, 60, 75, 85};
    int n = sizeof(prices) / sizeof(prices[0]);
    int span[n];

    calculateSpan(prices, n, span);

    printf("Stock Prices: ");
    printArray(prices, n);
    printf("Spans:        ");
    printArray(span, n);

    return 0;
}
