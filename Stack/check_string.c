#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a string is a valid number
bool isValidNumber(const char* str) {
    int i = 0;
    int dotCount = 0;

    // Handle optional leading sign
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    if (str[i] == '\0') {
        return false; // Sign only is not valid
    }

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            i++;
        } else if (str[i] == '.') {
            dotCount++;
            if (dotCount > 1) {
                return false; // More than one decimal point
            }
            i++;
        } else {
            return false; // Invalid character
        }
    }

    return true;
}

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to validate the mathematical expression
bool validateExpression(const char* expression) {
    int n = strlen(expression);
    char stack[n];
    int top = -1;

    bool expectNumber = true; // Start by expecting a number or '('

    for (int i = 0; i < n; i++) {
        char c = expression[i];

        if (isspace(c)) {
            continue; // Skip whitespace
        }

        if (c == '(') {
            stack[++top] = c; // Push '(' to the stack
            expectNumber = true; // After '(' we expect a number
        } else if (c == ')') {
            // Check for matching '('
            if (top == -1 || stack[top] != '(') {
                return false; // Mismatched parentheses
            }
            top--; // Pop the stack
            expectNumber = false; // After ')' we expect an operator
        } else if (isOperator(c)) {
            if (expectNumber) {
                return false; // Consecutive operators or operator at the start
            }
            expectNumber = true; // After an operator, we expect a number or '('
        } else {
            // Parse the number
            int j = i;
            while (j < n && (isdigit(expression[j]) || expression[j] == '.' || expression[j] == '+' || expression[j] == '-')) {
                j++;
            }

            char* token = (char*)malloc(j - i + 1);
            strncpy(token, expression + i, j - i);
            token[j - i] = '\0';

            if (!isValidNumber(token)) {
                free(token);
                return false; // Invalid number format
            }

            free(token);
            i = j - 1; // Move to the end of the number
            expectNumber = false; // After a number, we expect an operator or ')'
        }
    }

    // Check if all parentheses are closed
    if (top != -1) {
        return false; // Unmatched '('
    }

    return !expectNumber; // The expression must end with a number or ')'
}

// Main function to test the implementation
int main() {
    const char* expressions[] = {
        "12 + 34 - 5.67 * (89 / 4)",
        "12.34.56",
        "3..4",
        "abc + 12",
        "+123",
        "(1 + 2) * 3",
        "((1 + 2)",
        "1 + 2) * 3"
    };

    for (int i = 0; i < 8; i++) {
        printf("Expression: \"%s\"\n", expressions[i]);
        if (validateExpression(expressions[i])) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
        printf("\n");
    }

    return 0;
}
