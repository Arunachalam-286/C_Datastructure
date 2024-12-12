#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Mock implementation of the "knows" relationship.
// Modify this to reflect the actual problem input.
bool knows(int a, int b) {
    // Example matrix for testing (1 means "a knows b", 0 means "a doesn't know b").
    // This is a sample where person 2 is the celebrity.
    int matrix[4][4] = {
        {0, 1, 1, 1},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 1, 1, 0}
    };
    return matrix[a][b];
}

// Function to find the celebrity
int findCelebrity(int n) {
    // Create a stack and push all people onto it
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        stack[++top] = i;
    }

    // Narrow down to one potential celebrity
    while (top > 1) {
        int personA = stack[top--];
        int personB = stack[top--];

        if (knows(personA, personB)) {
            // If personA knows personB, personA cannot be a celebrity
            stack[++top] = personB;
        } else {
            // If personA doesn't know personB, personB cannot be a celebrity
            stack[++top] = personA;
        }
    }

    // Get the potential celebrity
    int candidate = stack[top--];
    free(stack);

    // Verify the candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            if (knows(candidate, i) || !knows(i, candidate)) {
                return -1; // No celebrity found
            }
        }
    }

    return candidate;
}

// Main function to test the implementation
int main() {
    int n = 4;  // Number of people
    int celebrity = findCelebrity(n);

    if (celebrity == -1) {
        printf("No celebrity found.\n");
    } else {
        printf("The celebrity is person %d.\n", celebrity);
    }

    return 0;
}
