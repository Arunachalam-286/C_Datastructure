#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to generate parentheses
void generateParentheses(int n, int openCount, int closeCount, char* current, int pos, char** result, int* count) {
    // Base case: If we have used all pairs of parentheses
    if (openCount == n && closeCount == n) {
        result[*count] = (char*)malloc((2 * n + 1) * sizeof(char));
        strcpy(result[*count], current);
        (*count)++;
        return;
    }

    // Add an open parenthesis if we haven't used all of them
    if (openCount < n) {
        current[pos] = '(';
        generateParentheses(n, openCount + 1, closeCount, current, pos + 1, result, count);
    }

    // Add a close parenthesis if it won't make the string invalid
    if (closeCount < openCount) {
        current[pos] = ')';
        generateParentheses(n, openCount, closeCount + 1, current, pos + 1, result, count);
    }
}

// Function to generate all valid parentheses
char** allValidParentheses(int n, int* returnSize) {
    int maxResults = 1 << (2 * n);  // Maximum possible combinations
    char** result = (char**)malloc(maxResults * sizeof(char*));
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));
    current[2 * n] = '\0';  // Null-terminate the string

    *returnSize = 0;
    generateParentheses(n, 0, 0, current, 0, result, returnSize);

    free(current);
    return result;
}

// Main function to test the implementation
int main() {
    int n = 3;  // Number of pairs of parentheses
    int returnSize;
    char** result = allValidParentheses(n, &returnSize);

    printf("Valid Parentheses for %d pairs:\n", n);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}
