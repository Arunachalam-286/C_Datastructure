#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the stack structure
typedef struct Stack {
    int top;
    int capacity;
    char* array;
} Stack;

// Function to create a stack of given capacity
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, char item) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push '%c'\n", item);
        return;
    }
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop\n");
        return '\0';
    }
    return stack->array[stack->top--];
}

// Function to reverse a string using a stack
void reverseString(char str[]) {
    int n = strlen(str);

    // Create a stack of sufficient size
    Stack* stack = createStack(n);

    // Push all characters of the string onto the stack
    for (int i = 0; i < n; i++) {
        push(stack, str[i]);
    }

    // Pop all characters from the stack and put them back into the string
    for (int i = 0; i < n; i++) {
        str[i] = pop(stack);
    }

    // Free the stack memory
    free(stack->array);
    free(stack);
}

// Main function to test the reverseString function
int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);

    reverseString(str);

    printf("Reversed string: %s\n", str);
    return 0;
}