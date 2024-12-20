#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Structure for the deque (Double-ended queue)
struct Deque {
    int items[MAX];
    int front;
    int rear;
};

// Initialize the deque
void initializeDeque(struct Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

// Check if the deque is empty
int isEmpty(struct Deque* deque) {
    return deque->front == -1;
}

// Check if the deque is full
int isFull(struct Deque* deque) {
    return deque->rear == MAX - 1;
}

// Add an element at the back of the deque
void enqueue(struct Deque* deque, int value) {
    if (isFull(deque)) {
        printf("Deque overflow\n");
        return;
    }
    if (isEmpty(deque)) {
        deque->front = 0;
    }
    deque->rear++;
    deque->items[deque->rear] = value;
}

// Remove an element from the front of the deque
int dequeue(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque underflow\n");
        return -1;
    }
    int value = deque->items[deque->front];
    deque->front++;
    if (deque->front > deque->rear) {
        deque->front = deque->rear = -1;
    }
    return value;
}

// Get the front element of the deque
int peekFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        return -1;
    }
    return deque->items[deque->front];
}

// Sliding Window Maximum function
void slidingWindowMaximum(int arr[], int n, int k) {
    struct Deque deque;
    initializeDeque(&deque);

    // Process first k elements
    for (int i = 0; i < k; i++) {
        while (!isEmpty(&deque) && arr[i] >= arr[peekFront(&deque)]) {
            dequeue(&deque);
        }
        enqueue(&deque, i);
    }

    // Print the maximum for the first window
    printf("Maximum in the first window: %d\n", arr[peekFront(&deque)]);

    // Process the rest of the elements
    for (int i = k; i < n; i++) {
        // Remove elements out of this window
        while (!isEmpty(&deque) && peekFront(&deque) <= i - k) {
            dequeue(&deque);
        }

        // Remove elements that are smaller than the current element
        while (!isEmpty(&deque) && arr[i] >= arr[peekFront(&deque)]) {
            dequeue(&deque);
        }

        // Add current element to the deque
        enqueue(&deque, i);

        // The element at the front of the deque is the largest in the current window
        printf("%d ", arr[peekFront(&deque)]);
    }
}

int main() {
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("Sliding Window Maximums:\n");
    slidingWindowMaximum(arr, n, k);

    return 0;
}
