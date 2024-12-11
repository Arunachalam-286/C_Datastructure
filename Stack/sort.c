#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
struct Stack {
    int data[MAX];
    int top;
};

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Function to get the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Recursive function to insert an element into a sorted stack
void sortedInsert(struct Stack* stack, int value) {
    if (isEmpty(stack) || value > peek(stack)) {
        push(stack, value);
        return;
    }

    int temp = pop(stack);
    sortedInsert(stack, value);

    push(stack, temp);
}

// Recursive function to sort a stack
void sortStack(struct Stack* stack) {
    if (!isEmpty(stack)) {
        int temp = pop(stack);
        sortStack(stack);
        sortedInsert(stack, temp);
    }
}

// Function to display the stack
void display(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }

    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initStack(&stack);

    push(&stack, 30);
    push(&stack, -5);
    push(&stack, 18);
    push(&stack, 14);
    push(&stack, -3);

    printf("Original stack:\n");
    display(&stack);

    sortStack(&stack);

    printf("Sorted stack:\n");
    display(&stack);

    return 0;
}