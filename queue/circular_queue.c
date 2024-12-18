#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum size of the queue

struct CircularQueue {
    int items[MAX];
    int front;
    int rear;
};

// Function to create an empty circular queue
void initializeQueue(struct CircularQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Check if the queue is full
int isFull(struct CircularQueue* queue) {
    return ((queue->rear + 1) % MAX == queue->front);
}

// Check if the queue is empty
int isEmpty(struct CircularQueue* queue) {
    return (queue->front == -1);
}

// Function to enqueue an element into the circular queue
void enqueue(struct CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) { // If the queue is empty
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % MAX;
    queue->items[queue->rear] = value;
    printf("Enqueued: %d\n", value);
}

// Function to dequeue an element from the circular queue
int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->items[queue->front];
    if (queue->front == queue->rear) { // If there is only one element in the queue
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX;
    }
    printf("Dequeued: %d\n", data);
    return data;
}

// Function to display the elements of the circular queue
void displayQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int i = queue->front;
    while (1) {
        printf("%d ", queue->items[i]);
        if (i == queue->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Main function to demonstrate the circular queue operations
int main() {
    struct CircularQueue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);
    enqueue(&queue, 50); // Queue is now full

    displayQueue(&queue);

    dequeue(&queue);
    dequeue(&queue);

    displayQueue(&queue);

    enqueue(&queue, 60);
    enqueue(&queue, 70); // Elements are added in circular fashion

    displayQueue(&queue);

    return 0;
}
