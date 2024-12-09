#include <stdio.h>
#include <stdlib.h>

// Definition of a queue node
struct Node {
    int data;
    struct Node* next;
};

// Definition of the queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to add an element to the queue (Enqueue)
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);

    // If the queue is empty, the new node is both front and rear
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        printf("%d enqueued to queue\n", data);
        return;
    }

    // Add the new node at the end and update the rear
    queue->rear->next = newNode;
    queue->rear = newNode;
    printf("%d enqueued to queue\n", data);
}

// Function to remove an element from the queue (Dequeue)
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }

    struct Node* temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;

    // If the front becomes NULL, update rear to NULL as well
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp); // Free the memory of the dequeued node
    return data;
}

// Function to get the front element of the queue
int peek(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

// Function to display the queue
void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* temp = queue->front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Example usage
int main() {
    struct Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    displayQueue(queue);

    printf("Dequeued element: %d\n", dequeue(queue));
    displayQueue(queue);

    printf("Front element: %d\n", peek(queue));

    return 0;
}