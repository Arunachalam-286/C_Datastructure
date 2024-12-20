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

// Function to interleave the queue
void interleaveQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot interleave.\n");
        return;
    }

    int n = queue->rear - queue->front + 1;

    // If the number of elements is odd, interleaving isn't possible
    if (n % 2 != 0) {
        printf("Queue has an odd number of elements. Cannot interleave.\n");
        return;
    }

    int half = n / 2;
    int stack[MAX];
    int top = -1;

    // Step 1: Push the first half of the queue into the stack
    for (int i = 0; i < half; i++) {
        stack[++top] = dequeue(queue);
    }

    // Step 2: Enqueue the elements from the stack back into the queue
    while (top != -1) {
        enqueue(queue, stack[top--]);
    }

    // Step 3: Move the first half elements to the back of the queue
    for (int i = 0; i < half; i++) {
        enqueue(queue, dequeue(queue));
    }

    // Step 4: Push the first half back into the stack
    for (int i = 0; i < half; i++) {
        stack[++top] = dequeue(queue);
    }

    // Step 5: Interleave the stack and the queue
    while (top != -1) {
        enqueue(queue, stack[top--]);
        enqueue(queue, dequeue(queue));
    }
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

    interleaveQueue(&queue);

    printf("Queue after interleaving:\n");
    displayQueue(&queue);

    return 0;
}
