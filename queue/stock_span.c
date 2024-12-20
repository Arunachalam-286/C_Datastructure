#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the queue

// Queue structure for storing indices
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

// Peek the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    return queue->items[queue->front];
}

// Function to calculate the stock span
void calculateStockSpan(int prices[], int n, int span[]) {
    struct Queue queue;
    initializeQueue(&queue);

    for (int i = 0; i < n; i++) {
        // Remove indices of elements that are less than the current price
        while (!isEmpty(&queue) && prices[peek(&queue)] <= prices[i]) {
            dequeue(&queue);
        }

        // Calculate span
        if (isEmpty(&queue)) {
            span[i] = i + 1; // All previous prices are smaller
        } else {
            span[i] = i - peek(&queue);
        }

        // Add the current index to the queue
        enqueue(&queue, i);
    }
}

// Display the stock span
void displayStockSpan(int prices[], int span[], int n) {
    printf("Day\tPrice\tSpan\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, prices[i], span[i]);
    }
}

// Main function to demonstrate the solution
int main() {
    int n;

    printf("Enter the number of days: ");
    scanf("%d", &n);

    int prices[n], span[n];

    printf("Enter the stock prices:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    calculateStockSpan(prices, n, span);

    printf("Stock Span for the given prices:\n");
    displayStockSpan(prices, span, n);

    return 0;
}
