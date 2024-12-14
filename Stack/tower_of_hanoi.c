#include <stdio.h>
#include <stdlib.h>

// Define a structure for a stack entry
typedef struct {
    int numDisks;  // Number of disks to move
    char source;   // Source peg
    char target;   // Target peg
    char auxiliary; // Auxiliary peg
} StackEntry;

// Define a stack structure
typedef struct {
    StackEntry* data; // Array to hold stack entries
    int top;          // Index of the top element
    int capacity;     // Maximum stack size
} Stack;

// Create a new stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (StackEntry*)malloc(capacity * sizeof(StackEntry));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push an entry onto the stack
void push(Stack* stack, int numDisks, char source, char target, char auxiliary) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->data[++stack->top] = (StackEntry){numDisks, source, target, auxiliary};
}

// Pop an entry from the stack
StackEntry pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Function to solve Tower of Hanoi using a stack
void towerOfHanoi(int n, char source, char target, char auxiliary) {
    // Create a stack to simulate the recursive calls
    Stack* stack = createStack(100); // Adjust size based on expected recursion depth

    // Push the initial state onto the stack
    push(stack, n, source, target, auxiliary);

    // Process the stack until it is empty
    while (!isEmpty(stack)) {
        // Pop the current state
        StackEntry current = pop(stack);

        if (current.numDisks == 1) {
            // Base case: Move one disk directly
            printf("Move disk 1 from %c to %c\n", current.source, current.target);
        } else {
            // Recursive case: Break the problem into smaller sub-problems

            // Step 3: Push the state to move n-1 disks from auxiliary to target
            push(stack, current.numDisks - 1, current.auxiliary, current.target, current.source);

            // Step 2: Push the state to move the largest disk from source to target
            push(stack, 1, current.source, current.target, current.auxiliary);

            // Step 1: Push the state to move n-1 disks from source to auxiliary
            push(stack, current.numDisks - 1, current.source, current.auxiliary, current.target);
        }
    }

    // Free the stack
    freeStack(stack);
}

// Main function
int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    printf("The sequence of moves:\n");
    towerOfHanoi(n, 'A', 'C', 'B'); // Source: A, Target: C, Auxiliary: B

    return 0;
}
