#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000  // Define a maximum size for the stacks

// Define a structure for the queue using two stacks
typedef struct {
    int stack1[MAX];  // Stack to enqueue elements
    int stack2[MAX];  // Stack to dequeue elements
    int top1;         // Top index for stack1
    int top2;         // Top index for stack2
} TwoStackQueue;

// Function to initialize the queue
void initQueue(TwoStackQueue* queue) {
    queue->top1 = -1;
    queue->top2 = -1;
}

// Function to check if the queue is empty
bool isEmpty(TwoStackQueue* queue) {
    return (queue->top1 == -1 && queue->top2 == -1);
}

// Function to enqueue an element
void enqueue(TwoStackQueue* queue, int value) {
    if (queue->top1 == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    queue->stack1[++(queue->top1)] = value;  // Push to stack1
    printf("Enqueued %d\n", value);
}

// Function to dequeue an element
int dequeue(TwoStackQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    // If stack2 is empty, transfer all elements from stack1 to stack2
    if (queue->top2 == -1) {
        while (queue->top1 != -1) {
            queue->stack2[++(queue->top2)] = queue->stack1[(queue->top1)--];  // Move elements to stack2
        }
    }

    // Pop from stack2 (the front of the queue)
    return queue->stack2[(queue->top2)--];
}

// Function to peek the front element of the queue
int peek(TwoStackQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    // If stack2 is empty, transfer all elements from stack1 to stack2
    if (queue->top2 == -1) {
        while (queue->top1 != -1) {
            queue->stack2[++(queue->top2)] = queue->stack1[(queue->top1)--];
        }
    }

    return queue->stack2[queue->top2];
}

// Function to check if the queue is empty
bool isQueueEmpty(TwoStackQueue* queue) {
    return isEmpty(queue);
}

// Main function to test the Two-Stack Queue implementation
int main() {
    TwoStackQueue queue;
    initQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Dequeued: %d\n", dequeue(&queue));  // Output: 10
    printf("Peek: %d\n", peek(&queue));        // Output: 20
    printf("Dequeued: %d\n", dequeue(&queue));  // Output: 20
    printf("Is the queue empty? %s\n", isQueueEmpty(&queue) ? "Yes" : "No");  // Output: No

    return 0;
}
