#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure for operators and operands
typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

typedef struct {
    double data[MAX_SIZE];
    int top;
} DoubleStack;

// Function prototypes
void pushChar(CharStack* stack, char value);
char popChar(CharStack* stack);
char peekChar(CharStack* stack);
int isEmptyChar(CharStack* stack);

void pushDouble(DoubleStack* stack, double value);
double popDouble(DoubleStack* stack);
int isEmptyDouble(DoubleStack* stack);

int precedence(char op);
int isOperator(char c);
void infixToPostfix(char* infix, char* postfix);
double evaluatePostfix(char* postfix);

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter a mathematical expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove newline character

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Result: %.2f\n", result);

    return 0;
}

// Stack functions for char
void pushChar(CharStack* stack, char value) {
    stack->data[++stack->top] = value;
}

char popChar(CharStack* stack) {
    return stack->data[stack->top--];
}

char peekChar(CharStack* stack) {
    return stack->data[stack->top];
}

int isEmptyChar(CharStack* stack) {
    return stack->top == -1;
}

// Stack functions for double
void pushDouble(DoubleStack* stack, double value) {
    stack->data[++stack->top] = value;
}

double popDouble(DoubleStack* stack) {
    return stack->data[stack->top--];
}

int isEmptyDouble(DoubleStack* stack) {
    return stack->top == -1;
}

// Helper functions
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    CharStack stack = {.top = -1};
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // If the character is a digit, append it to postfix
        if (isdigit(c)) {
            postfix[j++] = c;

            // Include multi-digit numbers
            while (isdigit(infix[i + 1]) || infix[i + 1] == '.') {
                postfix[j++] = infix[++i];
            }
            postfix[j++] = ' '; // Add space as a separator
        }
        // If the character is '(', push it onto the stack
        else if (c == '(') {
            pushChar(&stack, c);
        }
        // If the character is ')', pop until '(' is encountered
        else if (c == ')') {
            while (!isEmptyChar(&stack) && peekChar(&stack) != '(') {
                postfix[j++] = popChar(&stack);
                postfix[j++] = ' ';
            }
            popChar(&stack); // Remove '('
        }
        // If the character is an operator
        else if (isOperator(c)) {
            while (!isEmptyChar(&stack) && precedence(peekChar(&stack)) >= precedence(c)) {
                postfix[j++] = popChar(&stack);
                postfix[j++] = ' ';
            }
            pushChar(&stack, c);
        }
    }

    // Pop remaining operators from the stack
    while (!isEmptyChar(&stack)) {
        postfix[j++] = popChar(&stack);
        postfix[j++] = ' ';
    }

    postfix[j - 1] = '\0'; // Null-terminate the postfix expression
}

// Evaluate postfix expression
double evaluatePostfix(char* postfix) {
    DoubleStack stack = {.top = -1};

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        // If the character is a digit, parse the number and push it
        if (isdigit(c)) {
            double num = 0;

            // Handle multi-digit numbers
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }

            // Handle fractional part
            if (postfix[i] == '.') {
                double decimal = 0, divisor = 10;
                i++;
                while (isdigit(postfix[i])) {
                    decimal += (postfix[i++] - '0') / divisor;
                    divisor *= 10;
                }
                num += decimal;
            }

            pushDouble(&stack, num);
        }
        // If the character is an operator, pop two operands and apply the operator
        else if (isOperator(c)) {
            double b = popDouble(&stack);
            double a = popDouble(&stack);

            switch (c) {
                case '+': pushDouble(&stack, a + b); break;
                case '-': pushDouble(&stack, a - b); break;
                case '*': pushDouble(&stack, a * b); break;
                case '/': pushDouble(&stack, a / b); break;
            }
        }
    }

    return popDouble(&stack); // The final result
}
