#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // For sleep function (simulating time for calls)

#define MAX_AGENTS 3
#define MAX_CALLS 10

// Structure to represent a customer call
typedef struct {
    int callId;
    char* description;
} Call;

// Structure to represent an agent
typedef struct {
    int agentId;
    bool isAvailable;
} Agent;

// Structure for the call queue (FIFO)
typedef struct {
    Call* calls[MAX_CALLS];
    int front;
    int rear;
} CallQueue;

// Function to initialize a new call queue
void initQueue(CallQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is full
bool isQueueFull(CallQueue* queue) {
    return (queue->rear == MAX_CALLS - 1);
}

// Function to check if the queue is empty
bool isQueueEmpty(CallQueue* queue) {
    return (queue->front == -1);
}

// Function to add a call to the queue
void enqueue(CallQueue* queue, Call* newCall) {
    if (isQueueFull(queue)) {
        printf("Queue is full! Cannot accept more calls.\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->calls[++queue->rear] = newCall;
    printf("Call ID %d added to the queue.\n", newCall->callId);
}

// Function to remove a call from the queue
Call* dequeue(CallQueue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty! No calls to process.\n");
        return NULL;
    }
    Call* call = queue->calls[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return call;
}

// Function to initialize agents
void initAgents(Agent agents[], int numAgents) {
    for (int i = 0; i < numAgents; i++) {
        agents[i].agentId = i;
        agents[i].isAvailable = true;
    }
}

// Function to simulate the agent taking a call
void handleCall(Agent* agent, Call* call) {
    printf("Agent %d is handling Call ID %d: %s\n", agent->agentId, call->callId, call->description);
    agent->isAvailable = false;
    sleep(2); // Simulate call handling time
    printf("Agent %d has finished Call ID %d\n", agent->agentId, call->callId);
    agent->isAvailable = true;
}

// Main function to simulate the call center
int main() {
    // Initialize agents
    Agent agents[MAX_AGENTS];
    initAgents(agents, MAX_AGENTS);

    // Initialize the call queue
    CallQueue queue;
    initQueue(&queue);

    // Simulate incoming calls
    for (int i = 0; i < 10; i++) {
        Call* newCall = (Call*)malloc(sizeof(Call));
        newCall->callId = i + 1;
        newCall->description = "Customer call";
        enqueue(&queue, newCall);
    }

    // Simulate call handling
    while (!isQueueEmpty(&queue)) {
        // Check if there are any available agents
        for (int i = 0; i < MAX_AGENTS; i++) {
            if (agents[i].isAvailable) {
                Call* call = dequeue(&queue);
                if (call != NULL) {
                    handleCall(&agents[i], call);
                    free(call); // Free the memory of the processed call
                }
            }
        }
    }

    return 0;
}
