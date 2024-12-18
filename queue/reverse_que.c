#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum size of the queue

// Structure for the Queue
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Structure for the Stack
struct Stack {
    int items[MAX];
    int top;
};

// Initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Check if the queue is full
int isQueueFull(struct Queue* queue) {
    return (queue->rear == MAX - 1);
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    if (isQueueFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) { // Reset queue when empty
        queue->front = queue->rear = -1;
    }
    return value;
}

// Initialize the stack
void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isStackEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

// Check if the stack is full
int isStackFull(struct Stack* stack) {
    return (stack->top == MAX - 1);
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isStackFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->top++;
    stack->items[stack->top] = value;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    int value = stack->items[stack->top];
    stack->top--;
    return value;
}

// Display the elements of the queue
void displayQueue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

// Reverse the queue using a stack
void reverseQueue(struct Queue* queue) {
    struct Stack stack;
    initializeStack(&stack);

    // Dequeue elements from the queue and push them onto the stack
    while (!isQueueEmpty(queue)) {
        push(&stack, dequeue(queue));
    }

    // Pop elements from the stack and enqueue them back into the queue
    while (!isStackEmpty(&stack)) {
        enqueue(queue, pop(&stack));
    }
}

// Main function to demonstrate the reverse queue operation
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    printf("Original Queue:\n");
    displayQueue(&queue);

    reverseQueue(&queue);

    printf("Reversed Queue:\n");
    displayQueue(&queue);

    return 0;
}
