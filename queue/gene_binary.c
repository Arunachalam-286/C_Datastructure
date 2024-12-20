#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000 // Maximum size of the queue

// Structure for a Queue
struct Queue {
    char items[MAX][MAX];
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

// Enqueue a string into the queue
void enqueue(struct Queue* queue, char* value) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    strcpy(queue->items[queue->rear], value);
}

// Dequeue a string from the queue
char* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return NULL;
    }
    char* value = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    return value;
}

// Function to generate binary numbers from 1 to n
void generateBinaryNumbers(int n) {
    struct Queue queue;
    initializeQueue(&queue);

    // Enqueue the first binary number
    enqueue(&queue, "1");

    printf("Binary numbers from 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        // Dequeue the front binary number
        char* current = dequeue(&queue);
        printf("%s ", current);

        // Generate the next two binary numbers and enqueue them
        char next1[MAX], next2[MAX];
        sprintf(next1, "%s0", current);
        sprintf(next2, "%s1", current);

        enqueue(&queue, next1);
        enqueue(&queue, next2);
    }
    printf("\n");
}

// Main function to demonstrate the solution
int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input! n should be greater than 0.\n");
        return 1;
    }

    generateBinaryNumbers(n);

    return 0;
}
