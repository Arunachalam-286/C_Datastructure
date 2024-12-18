#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the queue

// Structure for the Queue
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
    return (queue->front == -1 || queue->front > queue->rear);
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Function to count the number of elements in the queue
int countElements(struct Queue* queue) {
    if (isEmpty(queue)) {
        return 0; // Queue is empty
    }
    return queue->rear - queue->front + 1; // Number of elements
}

// Main function to demonstrate the solution
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    // Enqueue some elements
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    // Count the number of elements
    int count = countElements(&queue);
    printf("Number of elements in the queue: %d\n", count);

    // Add another element and count again
    enqueue(&queue, 50);
    count = countElements(&queue);
    printf("Number of elements in the queue: %d\n", count);

    return 0;
}
