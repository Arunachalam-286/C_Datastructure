#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for queue nodes
typedef struct Node {
    char* value;  // String representing the number
    int remainder; // Remainder when divided by N
    struct Node* next;
} Node;

// Define a queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a node
void enqueue(Queue* queue, const char* value, int remainder) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = strdup(value); // Copy the string
    newNode->remainder = remainder;
    newNode->next = NULL;

    if (queue->rear) {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;

    if (!queue->front) {
        queue->front = newNode;
    }
}

// Function to dequeue a node
Node* dequeue(Queue* queue) {
    if (!queue->front) {
        return NULL;
    }
    Node* temp = queue->front;
    queue->front = queue->front->next;

    if (!queue->front) {
        queue->rear = NULL;
    }

    return temp;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to find the smallest multiple of N composed of only 0s and 1s
char* findSmallestMultiple(int N) {
    if (N == 0) {
        return NULL;
    }

    // Create a queue for BFS
    Queue* queue = createQueue();

    // Boolean array to keep track of visited remainders
    int visited[N];
    memset(visited, 0, sizeof(visited));

    // Enqueue the first number "1"
    enqueue(queue, "1", 1 % N);
    visited[1 % N] = 1;

    while (!isQueueEmpty(queue)) {
        // Dequeue a node
        Node* current = dequeue(queue);

        // Check if the current remainder is 0
        if (current->remainder == 0) {
            char* result = strdup(current->value);
            free(current->value);
            free(current);
            while (!isQueueEmpty(queue)) {
                Node* temp = dequeue(queue);
                free(temp->value);
                free(temp);
            }
            free(queue);
            return result;
        }

        // Generate the next numbers by appending "0" and "1"
        int remainder0 = (current->remainder * 10) % N;
        int remainder1 = (current->remainder * 10 + 1) % N;

        if (!visited[remainder0]) {
            char* nextValue = (char*)malloc(strlen(current->value) + 2);
            sprintf(nextValue, "%s0", current->value);
            enqueue(queue, nextValue, remainder0);
            visited[remainder0] = 1;
            free(nextValue);
        }

        if (!visited[remainder1]) {
            char* nextValue = (char*)malloc(strlen(current->value) + 2);
            sprintf(nextValue, "%s1", current->value);
            enqueue(queue, nextValue, remainder1);
            visited[remainder1] = 1;
            free(nextValue);
        }

        free(current->value);
        free(current);
    }

    // If no solution is found (shouldn't happen for positive N)
    free(queue);
    return NULL;
}

// Main function
int main() {
    int N;
    printf("Enter a number: ");
    scanf("%d", &N);

    char* result = findSmallestMultiple(N);
    if (result) {
        printf("Smallest multiple of %d composed of only 0s and 1s: %s\n", N, result);
        free(result);
    } else {
        printf("Invalid input or no solution found.\n");
    }

    return 0;
}
