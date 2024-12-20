#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Structure for the queue
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Initialize the queue
void initializeQueue(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Check if the queue is full
int isFull(struct Queue* queue) {
    return queue->rear == MAX - 1;
}

// Add an element at the back of the queue
void enqueue(struct Queue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Remove an element from the front of the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }
    int value = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return value;
}

// Function to find all subarrays with a sum greater than the given value
void findSubarraysWithSumGreaterThan(int arr[], int n, int targetSum) {
    int currentSum = 0;
    int start = 0;
    struct Queue queue;
    initializeQueue(&queue);

    // Traverse the array to find all subarrays
    for (int end = 0; end < n; end++) {
        // Add current element to the sum
        currentSum += arr[end];
        
        // Keep removing elements from the front of the window if sum exceeds targetSum
        while (currentSum > targetSum && start <= end) {
            // Enqueue the subarray from start to end
            enqueue(&queue, start);
            start++;
        }

        // Print the subarrays found in the current window
        while (!isEmpty(&queue)) {
            int startIdx = dequeue(&queue);
            printf("Subarray: [");
            for (int i = startIdx; i <= end; i++) {
                printf("%d ", arr[i]);
            }
            printf("]\n");
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int targetSum = 8;

    printf("Subarrays with sum greater than %d are:\n", targetSum);
    findSubarraysWithSumGreaterThan(arr, n, targetSum);

    return 0;
}
