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

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';  // Return null character if stack is empty
    }
    return stack->array[stack->top--];
}

// Function to check if two characters are a matching pair of parentheses
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Function to check if parentheses are balanced
int isBalanced(char* expression) {
    int n = strlen(expression);
    Stack* stack = createStack(n);

    for (int i = 0; i < n; i++) {
        char ch = expression[i];

        // If it's an opening bracket, push it onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(stack, ch);
        }
        // If it's a closing bracket
        else if (ch == ')' || ch == '}' || ch == ']') {
            // Pop from the stack and check for a matching pair
            if (isEmpty(stack) || !isMatchingPair(pop(stack), ch)) {
                free(stack->array);
                free(stack);
                return 0;  // Not balanced
            }
        }
    }

    // If the stack is empty, parentheses are balanced
    int balanced = isEmpty(stack);
    free(stack->array);
    free(stack);
    return balanced;
}

// Main function to test the isBalanced function
int main() {
    char expression[100];

    printf("Enter an expression: ");
    scanf("%s", expression);

    if (isBalanced(expression)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}