#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a stack entry
typedef struct {
    int row;    // Row index of the queen
    int col;    // Column index of the queen
} Queen;

// Define a stack structure
typedef struct {
    Queen* data;  // Array to hold queens
    int top;      // Index of the top queen
    int capacity; // Maximum number of queens (size of the board)
} Stack;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (Queen*)malloc(capacity * sizeof(Queen));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to push a queen onto the stack
void push(Stack* stack, int row, int col) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->data[++stack->top] = (Queen){row, col};
}

// Function to pop a queen from the stack
Queen pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to free the stack
void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Function to check if placing a queen at (row, col) is safe
bool isSafe(Stack* stack, int row, int col) {
    for (int i = 0; i <= stack->top; i++) {
        Queen q = stack->data[i];
        // Check for conflicts: same column, same diagonal
        if (q.col == col || abs(q.row - row) == abs(q.col - col)) {
            return false;
        }
    }
    return true;
}

// Function to print the board configuration
void printBoard(Stack* stack, int n) {
    char board[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
    for (int i = 0; i <= stack->top; i++) {
        Queen q = stack->data[i];
        board[q.row][q.col] = 'Q';
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to solve the N-Queens problem using a stack
void solveNQueens(int n) {
    Stack* stack = createStack(n);
    int row = 0, col = 0; // Start at the top-left corner

    while (row < n) {
        bool placed = false;
        // Try placing a queen in each column of the current row
        for (; col < n; col++) {
            if (isSafe(stack, row, col)) {
                push(stack, row, col);
                placed = true;
                row++;
                col = 0; // Reset column for the next row
                break;
            }
        }

        if (!placed) {
            // Backtrack: No valid column in the current row
            if (isEmpty(stack)) {
                break; // No more solutions
            }
            Queen lastQueen = pop(stack);
            row = lastQueen.row;
            col = lastQueen.col + 1; // Try the next column in the previous row
        }

        // If all queens are placed, print the solution
        if (stack->top == n - 1) {
            printBoard(stack, n);
            Queen lastQueen = pop(stack);
            row = lastQueen.row;
            col = lastQueen.col + 1; // Try the next column in the previous row
        }
    }

    freeStack(stack);
}

// Main function
int main() {
    int n;
    printf("Enter the value of N (number of queens): ");
    scanf("%d", &n);

    printf("Solutions for %d-Queens problem:\n", n);
    solveNQueens(n);

    return 0;
}
