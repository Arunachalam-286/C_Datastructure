#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a stack structure
typedef struct Stack {
    char** data;     // Array of strings to store states
    int top;         // Index of the top element
    int capacity;    // Maximum capacity of the stack
} Stack;

// Create a new stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char**)malloc(capacity * sizeof(char*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Push a state onto the stack
void push(Stack* stack, const char* state) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow.\n");
        return;
    }
    stack->data[++stack->top] = strdup(state);
}

// Pop a state from the stack
char* pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow.\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

// Peek the top state of the stack
char* peek(Stack* stack) {
    if (stack->top == -1) {
        return NULL;
    }
    return stack->data[stack->top];
}

// Free the stack
void freeStack(Stack* stack) {
    while (stack->top != -1) {
        free(stack->data[stack->top--]);
    }
    free(stack->data);
    free(stack);
}

// Undo/Redo system
typedef struct UndoRedoSystem {
    Stack* undoStack;  // Stack for undo actions
    Stack* redoStack;  // Stack for redo actions
    char* currentState;  // Current state
} UndoRedoSystem;

// Create an undo/redo system
UndoRedoSystem* createUndoRedoSystem(int capacity) {
    UndoRedoSystem* system = (UndoRedoSystem*)malloc(sizeof(UndoRedoSystem));
    system->undoStack = createStack(capacity);
    system->redoStack = createStack(capacity);
    system->currentState = NULL;
    return system;
}

// Perform an action
void performAction(UndoRedoSystem* system, const char* newState) {
    if (system->currentState != NULL) {
        push(system->undoStack, system->currentState);
    }
    system->currentState = strdup(newState);

    // Clear the redo stack
    while (system->redoStack->top != -1) {
        free(pop(system->redoStack));
    }
    printf("Performed action. Current state: %s\n", system->currentState);
}

// Undo the last action
void undo(UndoRedoSystem* system) {
    if (system->undoStack->top == -1) {
        printf("Nothing to undo.\n");
        return;
    }
    push(system->redoStack, system->currentState);
    system->currentState = pop(system->undoStack);
    printf("Undo performed. Current state: %s\n", system->currentState);
}

// Redo the last undone action
void redo(UndoRedoSystem* system) {
    if (system->redoStack->top == -1) {
        printf("Nothing to redo.\n");
        return;
    }
    push(system->undoStack, system->currentState);
    system->currentState = pop(system->redoStack);
    printf("Redo performed. Current state: %s\n", system->currentState);
}

// Free the undo/redo system
void freeUndoRedoSystem(UndoRedoSystem* system) {
    freeStack(system->undoStack);
    freeStack(system->redoStack);
    free(system->currentState);
    free(system);
}

// Main function to demonstrate the undo/redo system
int main() {
    UndoRedoSystem* system = createUndoRedoSystem(10);

    performAction(system, "State 1");
    performAction(system, "State 2");
    performAction(system, "State 3");

    undo(system);  // Undo to "State 2"
    undo(system);  // Undo to "State 1"
    redo(system);  // Redo to "State 2"

    performAction(system, "State 4");  // Perform a new action

    undo(system);  // Undo to "State 2"

    freeUndoRedoSystem(system);
    return 0;
}
