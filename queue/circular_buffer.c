#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Define the maximum size of the circular buffer

// Structure for the Circular Buffer (Queue)
struct CircularBuffer {
    int items[MAX];
    int front;
    int rear;
    int size; // To track the current size of the buffer
};

// Initialize the circular buffer
void initializeBuffer(struct CircularBuffer* buffer) {
    buffer->front = 0;
    buffer->rear = -1;
    buffer->size = 0;
}

// Check if the buffer is empty
int isEmpty(struct CircularBuffer* buffer) {
    return buffer->size == 0;
}

// Check if the buffer is full
int isFull(struct CircularBuffer* buffer) {
    return buffer->size == MAX;
}

// Add an element to the buffer
void enqueue(struct CircularBuffer* buffer, int value) {
    if (isFull(buffer)) {
        // Overwrite the oldest data
        buffer->front = (buffer->front + 1) % MAX;
        buffer->size--; // Decrease the size to accommodate the new value
    }

    buffer->rear = (buffer->rear + 1) % MAX;
    buffer->items[buffer->rear] = value;
    buffer->size++;
}

// Remove an element from the buffer
int dequeue(struct CircularBuffer* buffer) {
    if (isEmpty(buffer)) {
        printf("Buffer underflow\n");
        return -1;
    }

    int value = buffer->items[buffer->front];
    buffer->front = (buffer->front + 1) % MAX;
    buffer->size--;
    return value;
}

// Display the elements of the buffer
void displayBuffer(struct CircularBuffer* buffer) {
    if (isEmpty(buffer)) {
        printf("Buffer is empty\n");
        return;
    }

    printf("Buffer elements: ");
    for (int i = 0; i < buffer->size; i++) {
        int index = (buffer->front + i) % MAX;
        printf("%d ", buffer->items[index]);
    }
    printf("\n");
}

// Main function to demonstrate the solution
int main() {
    struct CircularBuffer buffer;
    initializeBuffer(&buffer);

    // Demonstrate enqueue operation
    enqueue(&buffer, 10);
    enqueue(&buffer, 20);
    enqueue(&buffer, 30);
    enqueue(&buffer, 40);
    enqueue(&buffer, 50);

    printf("After enqueue operations:\n");
    displayBuffer(&buffer);

    // Add another element to show circular overwrite
    enqueue(&buffer, 60);
    printf("After adding another element (overwriting oldest):\n");
    displayBuffer(&buffer);

    // Demonstrate dequeue operation
    printf("Dequeued: %d\n", dequeue(&buffer));
    printf("After dequeue operation:\n");
    displayBuffer(&buffer);

    // Add more elements
    enqueue(&buffer, 70);
    enqueue(&buffer, 80);
    printf("After adding more elements:\n");
    displayBuffer(&buffer);

    return 0;
}
