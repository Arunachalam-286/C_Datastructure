#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a print job
typedef struct PrintJob {
    int id;                 // Job ID
    char description[50];   // Job description
    int priority;           // Job priority (higher value = higher priority)
    struct PrintJob* next;  // Pointer to the next job in the queue
} PrintJob;

// Define a structure for the priority queue
typedef struct PriorityQueue {
    PrintJob* front;  // Pointer to the front of the queue
} PriorityQueue;

// Function to create a new print job
PrintJob* createPrintJob(int id, const char* description, int priority) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    newJob->id = id;
    strcpy(newJob->description, description);
    newJob->priority = priority;
    newJob->next = NULL;
    return newJob;
}

// Function to initialize a priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->front = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(PriorityQueue* queue) {
    return queue->front == NULL;
}

// Function to add a job to the priority queue
void enqueue(PriorityQueue* queue, PrintJob* job) {
    if (isQueueEmpty(queue) || queue->front->priority < job->priority) {
        // Insert at the front if the queue is empty or the new job has higher priority
        job->next = queue->front;
        queue->front = job;
    } else {
        // Find the correct position for the new job
        PrintJob* current = queue->front;
        while (current->next != NULL && current->next->priority >= job->priority) {
            current = current->next;
        }
        job->next = current->next;
        current->next = job;
    }
    printf("Job %d: \"%s\" with priority %d added to the queue.\n", job->id, job->description, job->priority);
}

// Function to remove a job from the priority queue
PrintJob* dequeue(PriorityQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("No jobs to process. The queue is empty.\n");
        return NULL;
    }
    PrintJob* job = queue->front;
    queue->front = queue->front->next;
    return job;
}

// Function to simulate job processing
void processJobs(PriorityQueue* queue) {
    while (!isQueueEmpty(queue)) {
        PrintJob* job = dequeue(queue);
        if (job) {
            printf("Processing Job %d: \"%s\" (Priority: %d)\n", job->id, job->description, job->priority);
            free(job); // Free memory after processing
        }
    }
    printf("All print jobs have been processed.\n");
}

// Main function
int main() {
    PriorityQueue* jobQueue = createPriorityQueue();

    // Add jobs to the queue
    enqueue(jobQueue, createPrintJob(1, "Print Invoice", 2));
    enqueue(jobQueue, createPrintJob(2, "Print Report", 5));
    enqueue(jobQueue, createPrintJob(3, "Print Presentation", 3));
    enqueue(jobQueue, createPrintJob(4, "Print Poster", 1));

    // Process jobs
    printf("\nStarting job processing...\n");
    processJobs(jobQueue);

    // Free the queue memory
    free(jobQueue);
    return 0;
}
