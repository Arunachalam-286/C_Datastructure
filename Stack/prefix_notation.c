#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Stack structure
typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack;

// Stack operations
void push(Stack* stack, double value) {
    stack->data[++stack->top] = value;
}

double pop(Stack* stack) {
    return stack->data[stack->top--];
}

// Function to evaluate a prefix expression
double evaluatePrefix(char* expression) {
    Stack stack = {.top = -1};
    int len = strlen(expression);

    // Traverse the expression from right to left
    for (int i = len - 1; i >= 0; i--) {
        char c = expression[i];

        // If the character is a digit, push it onto the stack
        if (isdigit(c)) {
            push(&stack, c - '0');
        }
        // If the character is an operator, pop two operands and perform the operation
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            double operand1 = pop(&stack);
            double operand2 = pop(&stack);

            switch (c) {
                case '+': push(&stack, operand1 + operand2); break;
                case '-': push(&stack, operand1 - operand2); break;
                case '*': push(&stack, operand1 * operand2); break;
                case '/': push(&stack, operand1 / operand2); break;
            }
        }
    }

    // The result will be at the top of the stack
    return pop(&stack);
}

int main() {
    char expression[MAX_SIZE];

    printf("Enter a prefix expression: ");
    fgets(expression, MAX_SIZE, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character

    double result = evaluatePrefix(expression);
    printf("Result: %.2f\n", result);

    return 0;
}
