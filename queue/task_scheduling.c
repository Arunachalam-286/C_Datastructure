#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a task
typedef struct Task {
    int id;            // Task ID
    char description[50]; // Task description
    int duration;      // Time required to complete the task (in seconds)
    struct Task* next; // Pointer to the next task in the queue
} Task;

// Define a structure for the task queue
typedef struct Queue {
    Task* front; // Pointer to the front of the queue
    Task* rear;  // Pointer to the rear of the queue
} Queue;

// Function to create a new task
Task* createTask(int id, const char* description, int duration) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->duration = duration;
    newTask->next = NULL;
    return newTask;
}

// Function to initialize a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a task
void enqueue(Queue* queue, Task* task) {
    if (isQueueEmpty(queue)) {
        queue->front = task;
        queue->rear = task;
    } else {
        queue->rear->next = task;
        queue->rear = task;
    }
    printf("Task %d: \"%s\" added to the queue.\n", task->id, task->description);
}

// Function to dequeue a task
Task* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("No tasks to process. The queue is empty.\n");
        return NULL;
    }
    Task* task = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return task;
}

// Function to simulate task processing
void processTasks(Queue* queue) {
    while (!isQueueEmpty(queue)) {
        Task* task = dequeue(queue);
        if (task) {
            printf("Processing Task %d: \"%s\" (Duration: %d seconds)\n", task->id, task->description, task->duration);
            sleep(task->duration); // Simulate task processing time
            printf("Task %d completed.\n", task->id);
            free(task); // Free the task memory after processing
        }
    }
    printf("All tasks have been processed.\n");
}

// Main function
int main() {
    Queue* taskQueue = createQueue();

    // Add tasks to the queue
    enqueue(taskQueue, createTask(1, "Download file", 3));
    enqueue(taskQueue, createTask(2, "Process data", 5));
    enqueue(taskQueue, createTask(3, "Generate report", 2));

    // Process tasks
    printf("\nStarting task processing...\n");
    processTasks(taskQueue);

    // Free the queue memory
    free(taskQueue);
    return 0;
}
