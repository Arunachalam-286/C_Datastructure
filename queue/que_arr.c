#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum size of the queue

// Queue structure
typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

// Function prototypes
Queue* createQueue();
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void displayQueue(Queue* queue);

int main() {
    Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("Queue after enqueues: ");
    displayQueue(queue);

    printf("Dequeued: %d\n", dequeue(queue));
    printf("Queue after dequeue: ");
    displayQueue(queue);

    return 0;
}

// Create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is full
int isFull(Queue* queue) {
    return queue->rear == MAX - 1;
}

// Check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

// Enqueue an element into the queue
void enqueue(Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue overflow. Cannot enqueue %d\n", value);
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->items[++queue->rear] = value;
}

// Dequeue an element from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow. Cannot dequeue\n");
        return -1;
    }
    return queue->items[queue->front++];
}

// Display the contents of the queue
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = queue->front; i <= queue->rear; i++) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}
