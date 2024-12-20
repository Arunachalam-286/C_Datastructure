#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Maximum size of the priority queue

// Structure for an element in the Priority Queue
struct Element {
    int data;      // The data value
    int priority;  // Priority of the element
};

// Structure for the Priority Queue
struct PriorityQueue {
    struct Element items[MAX];
    int size; // Current size of the priority queue
};

// Initialize the priority queue
void initializePriorityQueue(struct PriorityQueue* pq) {
    pq->size = 0;
}

// Check if the priority queue is empty
int isEmpty(struct PriorityQueue* pq) {
    return pq->size == 0;
}

// Check if the priority queue is full
int isFull(struct PriorityQueue* pq) {
    return pq->size == MAX;
}

// Enqueue an element into the priority queue
void enqueue(struct PriorityQueue* pq, int data, int priority) {
    if (isFull(pq)) {
        printf("Priority Queue is full\n");
        return;
    }

    // Add the element to the end of the array
    pq->items[pq->size].data = data;
    pq->items[pq->size].priority = priority;
    pq->size++;
}

// Dequeue the element with the highest priority
int dequeue(struct PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return -1;
    }

    // Find the element with the highest priority
    int highestPriorityIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->items[i].priority > pq->items[highestPriorityIndex].priority) {
            highestPriorityIndex = i;
        }
    }

    // Get the data of the element with the highest priority
    int data = pq->items[highestPriorityIndex].data;

    // Remove the element by shifting all elements after it
    for (int i = highestPriorityIndex; i < pq->size - 1; i++) {
        pq->items[i] = pq->items[i + 1];
    }
    pq->size--;

    return data;
}

// Display the elements in the priority queue
void display(struct PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return;
    }

    printf("Priority Queue elements (data, priority):\n");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->items[i].data, pq->items[i].priority);
    }
    printf("\n");
}

// Main function to demonstrate the Priority Queue
int main() {
    struct PriorityQueue pq;
    initializePriorityQueue(&pq);

    enqueue(&pq, 10, 1);
    enqueue(&pq, 20, 3);
    enqueue(&pq, 30, 2);

    printf("Initial Priority Queue:\n");
    display(&pq);

    printf("Dequeued element: %d\n", dequeue(&pq));

    printf("Priority Queue after dequeuing:\n");
    display(&pq);

    return 0;
}
