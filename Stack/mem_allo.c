#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a memory block structure
typedef struct MemoryBlock {
    void* address;              // Pointer to the memory block
    size_t size;                // Size of the memory block
    struct MemoryBlock* next;   // Pointer to the next block in the stack
} MemoryBlock;

// Define the stack structure
typedef struct MemoryStack {
    MemoryBlock* top;   // Top of the stack
    size_t totalSize;   // Total memory allocated
} MemoryStack;

// Initialize the memory stack
MemoryStack* createMemoryStack() {
    MemoryStack* stack = (MemoryStack*)malloc(sizeof(MemoryStack));
    stack->top = NULL;
    stack->totalSize = 0;
    return stack;
}

// Allocate memory and push it onto the stack
void* pushMemory(MemoryStack* stack, size_t size) {
    // Allocate memory block
    void* memory = malloc(size);
    if (!memory) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Create a new memory block node
    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    block->address = memory;
    block->size = size;
    block->next = stack->top;
    stack->top = block;

    stack->totalSize += size;
    printf("Allocated %zu bytes. Total allocated: %zu bytes.\n", size, stack->totalSize);
    return memory;
}

// Deallocate the most recently allocated memory block
void popMemory(MemoryStack* stack) {
    if (stack->top == NULL) {
        printf("No memory to deallocate.\n");
        return;
    }

    // Get the top memory block
    MemoryBlock* block = stack->top;
    stack->top = block->next;

    // Free the memory and update the total size
    stack->totalSize -= block->size;
    free(block->address);
    free(block);

    printf("Deallocated memory. Total allocated: %zu bytes.\n", stack->totalSize);
}

// Peek at the most recently allocated memory block
void* peekMemory(MemoryStack* stack) {
    if (stack->top == NULL) {
        printf("No memory to peek.\n");
        return NULL;
    }
    return stack->top->address;
}

// Free all allocated memory and destroy the stack
void freeMemoryStack(MemoryStack* stack) {
    while (stack->top) {
        popMemory(stack);
    }
    free(stack);
    printf("Memory stack destroyed.\n");
}

// Example usage
int main() {
    MemoryStack* stack = createMemoryStack();

    // Allocate memory
    int* arr1 = (int*)pushMemory(stack, 10 * sizeof(int));  // Allocate an array of 10 integers
    if (arr1) {
        for (int i = 0; i < 10; i++) {
            arr1[i] = i + 1;
        }
    }

    char* buffer = (char*)pushMemory(stack, 50 * sizeof(char));  // Allocate a character buffer
    if (buffer) {
        strcpy(buffer, "Hello, Stack-Based Memory Allocation!");
        printf("Buffer content: %s\n", buffer);
    }

    // Peek at the most recent allocation
    char* peekedBuffer = (char*)peekMemory(stack);
    if (peekedBuffer) {
        printf("Peeked buffer content: %s\n", peekedBuffer);
    }

    // Deallocate memory
    popMemory(stack);  // Deallocate the character buffer
    popMemory(stack);  // Deallocate the integer array

    // Free the memory stack
    freeMemoryStack(stack);

    return 0;
}
