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

// Recursive function to display elements of the queue
void displayQueueRecursive(struct Queue* queue, int index) {
    if (index > queue->rear) { // Base case: End of the queue
        return;
    }
    printf("%d ", queue->items[index]);
    displayQueueRecursive(queue, index + 1); // Recursive call for the next element
}

// Wrapper function to display the queue
void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    displayQueueRecursive(queue, queue->front); // Start from the front
    printf("\n");
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

    // Display the queue
    displayQueue(&queue);

    return 0;
}
