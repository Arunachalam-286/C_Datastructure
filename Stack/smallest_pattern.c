#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find the smallest number following the given pattern
void findSmallestNumber(char* pattern) {
    int n = strlen(pattern);
    int* stack = (int*)malloc((n + 1) * sizeof(int));
    int top = -1; // Initialize stack
    int num = 1;  // Start with number 1

    // Result array to store the final sequence
    char* result = (char*)malloc((n + 2) * sizeof(char));
    int resultIndex = 0;

    for (int i = 0; i <= n; i++) {
        // Push the current number onto the stack
        stack[++top] = num++;

        // If the pattern is 'I' or it's the last character, pop from stack
        if (i == n || pattern[i] == 'I') {
            while (top != -1) {
                result[resultIndex++] = stack[top--] + '0'; // Append to result
            }
        }
    }

    // Null-terminate the result string
    result[resultIndex] = '\0';

    // Print the result
    printf("Smallest number: %s\n", result);

    // Free allocated memory
    free(stack);
    free(result);
}

// Main function to test the solution
int main() {
    char pattern[100];
    printf("Enter the pattern (I/D): ");
    scanf("%s", pattern);

    findSmallestNumber(pattern);

    return 0;
}
