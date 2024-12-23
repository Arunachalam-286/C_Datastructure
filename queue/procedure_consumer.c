#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

// Circular Queue
typedef struct {
    int buffer[BUFFER_SIZE];
    int front;
    int rear;
    int count;
} Queue;

// Queue operations
void initQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

bool isQueueFull(Queue* queue) {
    return queue->count == BUFFER_SIZE;
}

bool isQueueEmpty(Queue* queue) {
    return queue->count == 0;
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->buffer[queue->rear] = item;
    queue->rear = (queue->rear + 1) % BUFFER_SIZE;
    queue->count++;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int item = queue->buffer[queue->front];
    queue->front = (queue->front + 1) % BUFFER_SIZE;
    queue->count--;
    return item;
}

// Shared resources
Queue sharedQueue;
pthread_mutex_t mutex;
pthread_cond_t notEmpty;
pthread_cond_t notFull;

// Producer function
void* producer(void* arg) {
    int item = 0;
    while (1) {
        sleep(rand() % 3); // Simulate production time
        item++;
        pthread_mutex_lock(&mutex);

        while (isQueueFull(&sharedQueue)) {
            printf("Producer waiting: Queue is full.\n");
            pthread_cond_wait(&notFull, &mutex);
        }

        enqueue(&sharedQueue, item);
        printf("Producer produced: %d\n", item);

        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    while (1) {
        sleep(rand() % 3); // Simulate consumption time
        pthread_mutex_lock(&mutex);

        while (isQueueEmpty(&sharedQueue)) {
            printf("Consumer waiting: Queue is empty.\n");
            pthread_cond_wait(&notEmpty, &mutex);
        }

        int item = dequeue(&sharedQueue);
        printf("Consumer consumed: %d\n", item);

        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Main function
int main() {
    pthread_t producerThread, consumerThread;

    // Initialize shared resources
    initQueue(&sharedQueue);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&notEmpty, NULL);
    pthread_cond_init(&notFull, NULL);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Join threads (optional, but ensures proper thread cleanup)
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&notEmpty);
    pthread_cond_destroy(&notFull);

    return 0;
}
