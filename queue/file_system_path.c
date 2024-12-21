#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the queue
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to enqueue an element
void enqueue(Queue* queue, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data); // Copy the string
    newNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    if (!queue->front) {
        queue->front = newNode;
    }
}

// Function to dequeue an element
void dequeue(Queue* queue) {
    if (!queue->front) {
        return;
    }
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(temp->data);
    free(temp);
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to simplify a path
char* simplifyPath(const char* path) {
    Queue* queue = createQueue();

    // Tokenize the input path
    char* pathCopy = strdup(path);
    char* token = strtok(pathCopy, "/");

    while (token) {
        if (strcmp(token, "..") == 0) {
            // If "..", remove the last valid directory from the queue
            if (!isQueueEmpty(queue)) {
                dequeue(queue);
            }
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            // If it's not "." or empty, add it to the queue
            enqueue(queue, token);
        }
        token = strtok(NULL, "/");
    }

    // Construct the simplified path
    char* simplifiedPath = (char*)malloc(1024);
    strcpy(simplifiedPath, "/");
    Node* current = queue->front;
    while (current) {
        strcat(simplifiedPath, current->data);
        current = current->next;
        if (current) {
            strcat(simplifiedPath, "/");
        }
    }

    // Free memory
    free(pathCopy);
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);

    return simplifiedPath;
}

// Main function
int main() {
    char path[1024];
    printf("Enter a file system path: ");
    scanf("%s", path);

    char* simplified = simplifyPath(path);
    printf("Simplified Path: %s\n", simplified);

    free(simplified);
    return 0;
}
