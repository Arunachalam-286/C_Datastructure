#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Structure for the stack
typedef struct {
    Node* top;      // Points to the top of the stack
    Node* middle;   // Points to the middle element
    int size;       // Current size of the stack
} Stack;

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = NULL;
    stack->middle = NULL;
    stack->size = 0;
}

// Push an element to the stack
void push(Stack* stack, int data) {
    Node* node = newNode(data);
    
    if (stack->top == NULL) {
        stack->top = node;
        stack->middle = node;
    } else {
        node->next = stack->top;
        stack->top->prev = node;
        stack->top = node;
        
        // Update middle pointer
        if (stack->size % 2 == 0) {
            stack->middle = stack->middle->prev;
        }
    }
    
    stack->size++;
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        return -1;  // Stack underflow
    }
    
    Node* temp = stack->top;
    int poppedValue = temp->data;
    
    stack->top = stack->top->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    }
    
    // Update middle pointer
    if (stack->size % 2 != 0) {
        stack->middle = stack->middle->next;
    }
    
    free(temp);
    stack->size--;
    
    return poppedValue;
}

// Retrieve the middle element in constant time
int getMiddle(Stack* stack) {
    if (stack->middle == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->middle->data;
}

// Delete the middle element
void deleteMiddle(Stack* stack) {
    if (stack->middle == NULL) {
        printf("Stack is empty\n");
        return;
    }
    
    Node* middleNode = stack->middle;
    
    // If there is only one element
    if (stack->size == 1) {
        stack->top = NULL;
        stack->middle = NULL;
    } else {
        // Adjust the pointers
        if (middleNode->prev != NULL) {
            middleNode->prev->next = middleNode->next;
        }
        if (middleNode->next != NULL) {
            middleNode->next->prev = middleNode->prev;
        }

        // Move the middle pointer
        if (stack->size % 2 == 0) {
            stack->middle = middleNode->next;
        } else {
            stack->middle = middleNode->prev;
        }
    }
    
    free(middleNode);
    stack->size--;
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->size == 0;
}

// Main function to demonstrate the stack operations
int main() {
    Stack stack;
    initStack(&stack);
    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);
    push(&stack, 50);
    
    printf("Middle Element: %d\n", getMiddle(&stack));  // Output: 30
    
    printf("Popped: %d\n", pop(&stack));  // Output: 50
    printf("Middle Element: %d\n", getMiddle(&stack));  // Output: 30
    
    deleteMiddle(&stack);  // Delete the middle element (30)
    printf("Middle Element after deletion: %d\n", getMiddle(&stack));  // Output: 20
    
    return 0;
}
