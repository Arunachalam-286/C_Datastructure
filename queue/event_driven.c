#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Event types
typedef enum {
    ARRIVAL,
    DEPARTURE
} EventType;

// Event structure
typedef struct Event {
    EventType type;
    int time;
    int queueIndex; // Index of the queue for departure events
    struct Event* next;
} Event;

// Queue structure for counters
typedef struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to enqueue an item
void enqueue(Queue* queue, int item) {
    if (queue->size == queue->capacity) {
        printf("Queue is full!\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
}

// Function to dequeue an item
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Priority queue for events
typedef struct PriorityQueue {
    Event* head;
} PriorityQueue;

// Function to create a priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->head = NULL;
    return pq;
}

// Function to insert an event into the priority queue
void insertEvent(PriorityQueue* pq, Event* event) {
    if (!pq->head || event->time < pq->head->time) {
        event->next = pq->head;
        pq->head = event;
    } else {
        Event* current = pq->head;
        while (current->next && current->next->time <= event->time) {
            current = current->next;
        }
        event->next = current->next;
        current->next = event;
    }
}

// Function to extract the next event
Event* extractEvent(PriorityQueue* pq) {
    if (!pq->head) return NULL;
    Event* event = pq->head;
    pq->head = pq->head->next;
    return event;
}

// Simulation function
void simulate(int numCounters, int simulationTime, int maxArrivalInterval, int maxServiceTime) {
    // Initialize counters and queues
    Queue* counters[numCounters];
    for (int i = 0; i < numCounters; i++) {
        counters[i] = createQueue(100);
    }

    // Initialize event priority queue
    PriorityQueue* eventQueue = createPriorityQueue();

    // Seed random number generator
    srand(42);

    // Generate initial arrival events
    for (int i = 0; i < 5; i++) {
        Event* event = (Event*)malloc(sizeof(Event));
        event->type = ARRIVAL;
        event->time = rand() % maxArrivalInterval;
        event->next = NULL;
        insertEvent(eventQueue, event);
    }

    // Run simulation
    int currentTime = 0;
    while (currentTime < simulationTime) {
        Event* event = extractEvent(eventQueue);
        if (!event) break;

        currentTime = event->time;

        if (event->type == ARRIVAL) {
            // Find the shortest queue
            int shortestQueue = 0;
            for (int i = 1; i < numCounters; i++) {
                if (counters[i]->size < counters[shortestQueue]->size) {
                    shortestQueue = i;
                }
            }

            // Add customer to the shortest queue
            enqueue(counters[shortestQueue], currentTime);
            printf("Customer arrives at time %d and joins queue %d\n", currentTime, shortestQueue);

            // Generate a departure event
            Event* departure = (Event*)malloc(sizeof(Event));
            departure->type = DEPARTURE;
            departure->time = currentTime + (rand() % maxServiceTime) + 1;
            departure->queueIndex = shortestQueue;
            departure->next = NULL;
            insertEvent(eventQueue, departure);

            // Generate the next arrival event
            Event* nextArrival = (Event*)malloc(sizeof(Event));
            nextArrival->type = ARRIVAL;
            nextArrival->time = currentTime + (rand() % maxArrivalInterval) + 1;
            nextArrival->next = NULL;
            insertEvent(eventQueue, nextArrival);

        } else if (event->type == DEPARTURE) {
            // Serve customer
            int servedCustomer = dequeue(counters[event->queueIndex]);
            printf("Customer served at time %d from queue %d\n", currentTime, event->queueIndex);
        }

        free(event);
    }

    // Clean up
    for (int i = 0; i < numCounters; i++) {
        free(counters[i]->data);
        free(counters[i]);
    }
    while (eventQueue->head) {
        Event* event = extractEvent(eventQueue);
        free(event);
    }
    free(eventQueue);
}

// Main function
int main() {
    int numCounters = 3;
    int simulationTime = 20;
    int maxArrivalInterval = 5;
    int maxServiceTime = 10;

    simulate(numCounters, simulationTime, maxArrivalInterval, maxServiceTime);

    return 0;
}
