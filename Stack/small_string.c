#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Function prototypes
Stack* createStack();
void push(Stack* stack, int value);
int pop(Stack* stack);
int isEmpty(Stack* stack);
char* smallestStringFromPattern(const char* pattern);

int main() {
    char pattern[] = "IDID";
    printf("Smallest string following the pattern \"%s\": %s\n", pattern, smallestStringFromPattern(pattern));
    return 0;
}

// Function to create a stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Function to push an item onto the stack
void push(Stack* stack, int value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

// Function to pop an item from the stack
int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to find the smallest string following the given pattern
char* smallestStringFromPattern(const char* pattern) {
    int n = strlen(pattern);
    char* result = (char*)malloc((n + 2) * sizeof(char)); // Result string
    int num = 1; // Start with digit 1
    Stack* stack = createStack(); // Create a stack
    int index = 0; // Index for the result string

    // Process each character in the pattern
    for (int i = 0; i < n; i++) {
        push(stack, num++);
        if (pattern[i] == 'I') {
            while (!isEmpty(stack)) {
                result[index++] = pop(stack) + '0'; // Convert to character
            }
        }
    }

    // Push the last number and empty the stack
    push(stack, num);
    while (!isEmpty(stack)) {
        result[index++] = pop(stack) + '0';
    }

    result[index] = '\0'; // Null-terminate the string
    free(stack);
    return result;
}
