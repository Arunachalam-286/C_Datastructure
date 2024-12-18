#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum size of the queue

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

// Check if the queue is full
int isFull(struct Queue* queue) {
    return (queue->rear == MAX - 1);
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) { // If the queue is empty
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
    printf("Enqueued: %d\n", value);
}

// Dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->items[queue->front];
    queue->front++;
    printf("Dequeued: %d\n", data);
    if (queue->front > queue->rear) { // Reset queue when empty
        queue->front = queue->rear = -1;
    }
    return data;
}

// Peek at the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->items[queue->front];
}

// Display the elements of the queue
void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

// Main function to demonstrate queue operations
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Front element: %d\n", peek(&queue));
    displayQueue(&queue);

    dequeue(&queue);
    printf("Front element after dequeue: %d\n", peek(&queue));
    displayQueue(&queue);

    enqueue(&queue, 40);
    enqueue(&queue, 50);
    displayQueue(&queue);

    dequeue(&queue);
    dequeue(&queue);
    displayQueue(&queue);

    return 0;
}
