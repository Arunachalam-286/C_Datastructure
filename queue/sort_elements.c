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
    return queue->front == -1;
}

// Check if the queue is full
int isFull(struct Queue* queue) {
    return queue->rear == MAX - 1;
}

// Enqueue an element into the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    int value = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    return value;
}

// Find the minimum value in the queue
int findMinIndex(struct Queue* queue, int sortedUntil) {
    int minIndex = -1;
    int minValue = __INT_MAX__;
    int size = queue->rear - queue->front + 1;

    for (int i = 0; i < size; i++) {
        int current = dequeue(queue);
        if (i <= sortedUntil && current < minValue) {
            minValue = current;
            minIndex = i;
        }
        enqueue(queue, current); // Re-enqueue the element
    }

    return minIndex;
}

// Place the minimum value at the rear
void moveToRear(struct Queue* queue, int minIndex) {
    int size = queue->rear - queue->front + 1;

    for (int i = 0; i < size; i++) {
        int current = dequeue(queue);
        if (i != minIndex) {
            enqueue(queue, current); // Re-enqueue all elements except the minIndex
        } else {
            enqueue(queue, current); // Place the minimum value at the rear
        }
    }
}

// Function to sort the queue
void sortQueue(struct Queue* queue) {
    int size = queue->rear - queue->front + 1;

    for (int i = 0; i < size; i++) {
        int minIndex = findMinIndex(queue, size - i - 1);
        moveToRear(queue, minIndex);
    }
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

// Main function to demonstrate the solution
int main() {
    struct Queue queue;
    initializeQueue(&queue);

    int n, value;

    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    printf("Enter the elements of the queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        enqueue(&queue, value);
    }

    printf("Original Queue:\n");
    displayQueue(&queue);

    sortQueue(&queue);

    printf("Sorted Queue:\n");
    displayQueue(&queue);

    return 0;
}
