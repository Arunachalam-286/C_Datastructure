#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256 // Maximum possible unique characters (ASCII)

// Structure for the Queue
struct Queue {
    char items[MAX];
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

// Enqueue an element into the queue
void enqueue(struct Queue* queue, char value) {
    if (queue->rear == MAX - 1) {
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
char dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return '\0';
    }
    char value = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    return value;
}

// Peek the front element of the queue
char peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        return '\0';
    }
    return queue->items[queue->front];
}

// Function to find the first non-repeating character in a stream
void firstNonRepeating(char* stream) {
    struct Queue queue;
    initializeQueue(&queue);

    int charCount[MAX] = {0}; // Array to store the frequency of each character

    printf("Stream: %s\n", stream);
    printf("First non-repeating characters: ");

    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];

        // Increment the count of the character
        charCount[ch]++;

        // Enqueue the character into the queue
        enqueue(&queue, ch);

        // Check the front of the queue for non-repeating character
        while (!isEmpty(&queue) && charCount[peek(&queue)] > 1) {
            dequeue(&queue); // Remove characters that are repeating
        }

        // Display the first non-repeating character
        if (!isEmpty(&queue)) {
            printf("%c ", peek(&queue));
        } else {
            printf("-1 "); // No non-repeating character found
        }
    }
    printf("\n");
}

// Main function to demonstrate the solution
int main() {
    char stream[] = "aabcbded";
    firstNonRepeating(stream);

    char stream2[] = "xyzxy";
    firstNonRepeating(stream2);

    return 0;
}
