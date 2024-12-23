#include <stdio.h>
#include <stdlib.h>

// Define the queue structure
typedef struct Queue {
    int* data;
    int front, rear, size, capacity;
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
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to enqueue an element
void enqueue(Queue* queue, int value) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = value;
        queue->size++;
    }
}

// Function to dequeue an element
int dequeue(Queue* queue) {
    if (!isEmpty(queue)) {
        int value = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return value;
    }
    return -1;
}

// Function to solve the Josephus problem using a queue
int josephus(int n, int k) {
    // Create a queue and initialize it with people 1 to n
    Queue* queue = createQueue(n);
    for (int i = 1; i <= n; i++) {
        enqueue(queue, i);
    }

    // Simulate the elimination process
    while (queue->size > 1) {
        // Skip the first k-1 people by dequeuing and re-enqueuing
        for (int i = 1; i < k; i++) {
            enqueue(queue, dequeue(queue));
        }
        // Eliminate the k-th person
        dequeue(queue);
    }

    // The last person remaining is the winner
    int winner = dequeue(queue);
    free(queue->data);
    free(queue);
    return winner;
}

// Main function to test the Josephus problem solution
int main() {
    int n = 7; // Number of people
    int k = 3; // Step size

    int result = josephus(n, k);
    printf("The winner is person %d.\n", result);

    return 0;
}
