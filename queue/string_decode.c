#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a queue node
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Define the queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a character
void enqueue(Queue* queue, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newNode;
    } else {
        queue->front = newNode;
    }
    queue->rear = newNode;
}

// Function to dequeue a character
char dequeue(Queue* queue) {
    if (!queue->front) return '\0';
    Node* temp = queue->front;
    char c = temp->data;
    queue->front = temp->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(temp);
    return c;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Helper function to parse a number from the queue
int parseNumber(Queue* queue) {
    int num = 0;
    while (!isEmpty(queue) && isdigit(queue->front->data)) {
        num = num * 10 + (dequeue(queue) - '0');
    }
    return num;
}

// Recursive function to decode a string
char* decodeString(Queue* queue) {
    char* result = (char*)malloc(1000 * sizeof(char)); // Buffer for the decoded string
    int idx = 0;

    while (!isEmpty(queue)) {
        char c = dequeue(queue);

        if (isdigit(c)) {
            // Parse the number
            enqueue(queue, c); // Re-enqueue the digit for parseNumber
            int repeat = parseNumber(queue);

            // Skip the '['
            if (!isEmpty(queue) && queue->front->data == '[') {
                dequeue(queue);
            }

            // Recursively decode the substring inside the brackets
            char* inner = decodeString(queue);

            // Append the decoded substring 'repeat' times
            for (int i = 0; i < repeat; i++) {
                strcpy(result + idx, inner);
                idx += strlen(inner);
            }
            free(inner);
        } else if (c == ']') {
            // End of current recursion
            break;
        } else {
            // Append regular characters
            result[idx++] = c;
        }
    }

    result[idx] = '\0'; // Null-terminate the string
    return result;
}

// Main function to decode the input string
char* decode(const char* s) {
    // Initialize the queue
    Queue* queue = createQueue();
    for (int i = 0; s[i] != '\0'; i++) {
        enqueue(queue, s[i]);
    }

    // Decode the string
    char* result = decodeString(queue);

    // Free the queue
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);

    return result;
}

// Main function to test the decoding function
int main() {
    char* input = "3[a2[c]]";
    char* output = decode(input);
    printf("Decoded string: %s\n", output);
    free(output);

    return 0;
}
