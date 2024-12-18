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

// Function to print the first k elements of the queue without altering its structure
void printFirstKElements(struct Queue* queue, int k) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    if (k > queue->rear - queue->front + 1) {
        printf("There are fewer than %d elements in the queue\n", k);
        return;
    }
    
    printf("First %d elements of the queue: ", k);
    for (int i = queue->front; i < queue->front + k; i++) {
        printf("%d ", queue->items[i]);
    }
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
    enqueue(&queue, 50);

    int k = 3; // Number of elements to display
    printFirstKElements(&queue, k);

    return 0;
}
