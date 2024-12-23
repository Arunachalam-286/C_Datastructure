#include <stdio.h>
#include <stdlib.h>

// Define a queue structure
typedef struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to check if the queue is full
int isQueueFull(Queue* queue) {
    return queue->size == queue->capacity;
}

// Function to enqueue an element
void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue is full! Cannot add more people.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
}

// Function to dequeue an element
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! Nothing to dequeue.\n");
        return -1;
    }
    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Function to count the number of people with age greater than x
int countPeopleWithAgeGreaterThan(Queue* queue, int x) {
    int count = 0;
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        if (queue->data[index] > x) {
            count++;
        }
    }
    return count;
}

// Main function to test the implementation
int main() {
    int capacity = 10;
    Queue* queue = createQueue(capacity);

    // Add ages to the queue
    enqueue(queue, 25);
    enqueue(queue, 30);
    enqueue(queue, 18);
    enqueue(queue, 40);
    enqueue(queue, 35);

    int x = 20;
    int result = countPeopleWithAgeGreaterThan(queue, x);

    printf("Number of people with age greater than %d: %d\n", x, result);

    // Clean up
    free(queue->data);
    free(queue);

    return 0;
}
