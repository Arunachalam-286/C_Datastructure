#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the stack

// Stack structure
struct Stack {
    int items[MAX];
    int top;
};

// Initialize a stack
void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->items[++stack->top] = value;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Peek the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top];
}

// Queue structure using two stacks
struct Queue {
    struct Stack stack1;
    struct Stack stack2;
};

// Initialize the queue
void initializeQueue(struct Queue* queue) {
    initializeStack(&queue->stack1);
    initializeStack(&queue->stack2);
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    push(&queue->stack1, value);
}

// Dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(&queue->stack2)) {
        // Transfer all elements from stack1 to stack2 if stack2 is empty
        while (!isEmpty(&queue->stack1)) {
            push(&queue->stack2, pop(&queue->stack1));
        }
    }

    if (isEmpty(&queue->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }

    return pop(&queue->stack2);
}

// Display elements of the queue
void displayQueue(struct Queue* queue) {
    if (isEmpty(&queue->stack1) && isEmpty(&queue->stack2)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements (front to rear): ");
    // Display stack2 (elements already reversed for dequeue)
    for (int i = queue->stack2.top; i >= 0; i--) {
        printf("%d ", queue->stack2.items[i]);
    }

    // Display stack1 in order (not reversed yet)
    for (int i = 0; i <= queue->stack1.top; i++) {
        printf("%d ", queue->stack1.items[i]);
    }
    printf("\n");
}

// Main function to demonstrate the Queue using two stacks
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    printf("After enqueue operations:\n");
    displayQueue(&queue);

    printf("Dequeued element: %d\n", dequeue(&queue));
    printf("After one dequeue operation:\n");
    displayQueue(&queue);

    enqueue(&queue, 40);
    printf("After enqueueing 40:\n");
    displayQueue(&queue);

    return 0;
}
