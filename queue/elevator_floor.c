#include <stdio.h>
#include <stdlib.h>

// Define a structure for a queue node
typedef struct QueueNode {
    int floor;
    struct QueueNode* next;
} QueueNode;

// Define a structure for a queue
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create a new queue node
QueueNode* createQueueNode(int floor) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->floor = floor;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a floor request
void enqueue(Queue* queue, int floor) {
    QueueNode* newNode = createQueueNode(floor);
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Floor %d request added to the queue.\n", floor);
}

// Function to dequeue a floor request
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. No floor requests to process.\n");
        return -1;
    }
    QueueNode* temp = queue->front;
    int floor = temp->floor;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    printf("Processing floor %d request.\n", floor);
    return floor;
}

// Function to display the current queue
void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("No floor requests in the queue.\n");
        return;
    }
    QueueNode* temp = queue->front;
    printf("Current floor requests in queue: ");
    while (temp) {
        printf("%d ", temp->floor);
        temp = temp->next;
    }
    printf("\n");
}

// Example usage
int main() {
    Queue* elevatorQueue = createQueue();

    // Simulate adding floor requests
    enqueue(elevatorQueue, 5);
    enqueue(elevatorQueue, 2);
    enqueue(elevatorQueue, 8);

    // Display the queue
    displayQueue(elevatorQueue);

    // Simulate processing floor requests
    dequeue(elevatorQueue);
    dequeue(elevatorQueue);

    // Display the queue again
    displayQueue(elevatorQueue);

    // Process remaining requests
    dequeue(elevatorQueue);
    dequeue(elevatorQueue); // Attempt to process an empty queue

    // Clean up
    free(elevatorQueue);
    return 0;
}
