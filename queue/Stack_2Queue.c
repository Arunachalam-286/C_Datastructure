#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the queue

// Structure for a Queue
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Check if the queue is full
int isFull(struct Queue* queue) {
    return queue->rear == MAX - 1;
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    return data;
}

// Peek the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->items[queue->front];
}

// Stack structure using two queues
struct Stack {
    struct Queue queue1;
    struct Queue queue2;
};

// Initialize the stack
void initializeStack(struct Stack* stack) {
    initializeQueue(&stack->queue1);
    initializeQueue(&stack->queue2);
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    enqueue(&stack->queue1, value);
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(&stack->queue1)) {
        printf("Stack is empty\n");
        return -1;
    }

    // Transfer elements from queue1 to queue2, except the last one
    while (stack->queue1.front != stack->queue1.rear) {
        enqueue(&stack->queue2, dequeue(&stack->queue1));
    }

    // The last element in queue1 is the top of the stack
    int poppedValue = dequeue(&stack->queue1);

    // Swap queue1 and queue2
    struct Queue temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;

    return poppedValue;
}

// Display elements in the stack
void displayStack(struct Stack* stack) {
    if (isEmpty(&stack->queue1)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements (top to bottom): ");
    for (int i = stack->queue1.front; i <= stack->queue1.rear; i++) {
        printf("%d ", stack->queue1.items[i]);
    }
    printf("\n");
}

// Main function to demonstrate the Stack using two queues
int main() {
    struct Stack stack;
    initializeStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printf("After push operations:\n");
    displayStack(&stack);

    printf("Popped element: %d\n", pop(&stack));
    printf("After one pop operation:\n");
    displayStack(&stack);

    push(&stack, 40);
    printf("After pushing 40:\n");
    displayStack(&stack);

    return 0;
}
