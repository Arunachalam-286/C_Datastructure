#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a queue node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the structure for a queue
typedef struct Queue {
    Node* front;  // Front of the queue
    Node* rear;   // Rear of the queue
    int size;     // Size of the queue
} Queue;

// Function to initialize a queue
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Function to check if the queue is empty
bool isEmptyQueue(Queue* queue) {
    return queue->size == 0;
}

// Function to enqueue an element
void enqueue(Queue* queue, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->size++;
}

// Function to dequeue an element
int dequeue(Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue is empty\n");
        return -1;  // Queue underflow
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

// Function to get the front element of the queue without removing it
int front(Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

// Define the structure for the stack
typedef struct {
    Queue queue1;  // Primary queue
    Queue queue2;  // Secondary queue
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    initQueue(&stack->queue1);
    initQueue(&stack->queue2);
}

// Function to check if the stack is empty
bool isEmptyStack(Stack* stack) {
    return isEmptyQueue(&stack->queue1);
}

// Function to push an element onto the stack
void push(Stack* stack, int data) {
    enqueue(&stack->queue1, data);
    printf("Pushed %d\n", data);
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is empty\n");
        return -1;  // Stack underflow
    }

    // Move all elements except the last from queue1 to queue2
    while (stack->queue1.size > 1) {
        enqueue(&stack->queue2, dequeue(&stack->queue1));
    }

    // The last element in queue1 is the top of the stack
    int poppedValue = dequeue(&stack->queue1);

    // Swap queue1 and queue2
    Queue temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;

    printf("Popped %d\n", poppedValue);
    return poppedValue;
}

// Function to get the top element of the stack
int top(Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is empty\n");
        return -1;
    }

    // Move all elements except the last from queue1 to queue2
    while (stack->queue1.size > 1) {
        enqueue(&stack->queue2, dequeue(&stack->queue1));
    }

    // The last element in queue1 is the top of the stack
    int topValue = front(&stack->queue1);

    // Move the last element to queue2
    enqueue(&stack->queue2, dequeue(&stack->queue1));

    // Swap queue1 and queue2
    Queue temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;

    return topValue;
}

// Main function to demonstrate the stack operations
int main() {
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top Element: %d\n", top(&stack));  // Output: 30
    printf("Popped: %d\n", pop(&stack));      // Output: 30
    printf("Top Element: %d\n", top(&stack));  // Output: 20
    printf("Popped: %d\n", pop(&stack));      // Output: 20

    return 0;
}
