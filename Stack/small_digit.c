#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove k digits to get the smallest possible number
char* removeKdigits(char* num, int k) {
    int n = strlen(num);
    if (k == n) {
        // If all digits are removed, return "0"
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }

    // Stack to store the digits of the result
    char* stack = (char*)malloc((n + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        // While the stack is not empty, and the current digit is smaller than the top of the stack
        // and we still have digits to remove
        while (top >= 0 && stack[top] > num[i] && k > 0) {
            top--;  // Pop the stack
            k--;
        }
        stack[++top] = num[i];  // Push the current digit
    }

    // If there are still digits to remove, remove them from the top
    top -= k;

    // Construct the result
    stack[top + 1] = '\0';  // Null-terminate the stack string

    // Remove leading zeros
    char* result = stack;
    while (*result == '0' && *(result + 1) != '\0') {
        result++;
    }

    // If result is empty, return "0"
    if (*result == '\0') {
        result = "0";
    }

    return strdup(result);  // Return the result
}

// Main function to test the implementation
int main() {
    char num[] = "1432219";
    int k = 3;

    char* result = removeKdigits(num, k);
    printf("Result after removing %d digits: %s\n", k, result);
    free(result);  // Free the allocated memory

    char num2[] = "10200";
    k = 1;
    result = removeKdigits(num2, k);
    printf("Result after removing %d digits: %s\n", k, result);
    free(result);

    char num3[] = "10";
    k = 2;
    result = removeKdigits(num3, k);
    printf("Result after removing %d digits: %s\n", k, result);
    free(result);

    return 0;
}
