#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a stack structure
typedef struct Stack {
    char** data;  // Array of strings
    int top;      // Top of the stack
    int capacity; // Maximum capacity
} Stack;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char**)malloc(capacity * sizeof(char*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to push a string onto the stack
void push(Stack* stack, const char* dir) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->data[++stack->top] = strdup(dir); // Allocate memory for the string
}

// Function to pop a string from the stack
void pop(Stack* stack) {
    if (stack->top == -1) {
        return;
    }
    free(stack->data[stack->top--]); // Free the memory for the string
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to free the stack
void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack->data);
    free(stack);
}

// Function to simplify a file system path
char* simplifyPath(const char* path) {
    Stack* stack = createStack(100);
    char* result = (char*)malloc(strlen(path) + 1);
    strcpy(result, path);

    // Tokenize the input path by "/"
    char* token = strtok(result, "/");
    while (token != NULL) {
        if (strcmp(token, "..") == 0) {
            // Move to the parent directory (pop from stack if not empty)
            if (!isEmpty(stack)) {
                pop(stack);
            }
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            // Push valid directory name onto the stack
            push(stack, token);
        }
        token = strtok(NULL, "/");
    }

    // Rebuild the simplified path from the stack
    char* simplifiedPath = (char*)malloc(strlen(path) + 1);
    simplifiedPath[0] = '\0';

    if (isEmpty(stack)) {
        strcat(simplifiedPath, "/");
    } else {
        for (int i = 0; i <= stack->top; i++) {
            strcat(simplifiedPath, "/");
            strcat(simplifiedPath, stack->data[i]);
        }
    }

    free(result);
    freeStack(stack);
    return simplifiedPath;
}

// Main function
int main() {
    char path[100];
    printf("Enter a file system path: ");
    scanf("%s", path);

    char* simplifiedPath = simplifyPath(path);
    printf("Simplified Path: %s\n", simplifiedPath);

    free(simplifiedPath);
    return 0;
}
