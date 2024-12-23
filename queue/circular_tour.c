#include <stdio.h>
#include <stdlib.h>

// Define a structure for the petrol pump
typedef struct PetrolPump {
    int petrol;
    int distance;
} PetrolPump;

// Define a structure for the queue
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

// Function to enqueue an element
void enqueue(Queue* queue, int value) {
    if (queue->size == queue->capacity) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

// Function to dequeue an element
int dequeue(Queue* queue) {
    if (queue->size == 0) {
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to solve the Circular Tour problem
int circularTour(PetrolPump pumps[], int n) {
    Queue* queue = createQueue(n);
    int current_petrol = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        enqueue(queue, i);
        current_petrol += pumps[i].petrol - pumps[i].distance;

        // If current petrol is negative, remove elements from the queue
        while (current_petrol < 0 && !isQueueEmpty(queue)) {
            int removed = dequeue(queue);
            current_petrol -= pumps[removed].petrol - pumps[removed].distance;
            start = removed + 1;
        }
    }

    // Check if the tour is possible
    if (current_petrol >= 0 && start < n) {
        return start;
    } else {
        return -1; // No valid starting point
    }
}

// Main function
int main() {
    PetrolPump pumps[] = {
        {6, 4},
        {3, 6},
        {7, 3}
    };
    int n = sizeof(pumps) / sizeof(pumps[0]);

    int start = circularTour(pumps, n);
    if (start != -1) {
        printf("The truck can start at petrol pump %d\n", start);
    } else {
        printf("No valid starting point exists.\n");
    }

    return 0;
}
