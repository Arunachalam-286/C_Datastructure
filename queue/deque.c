#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Maximum size of the deque

struct Deque {
    int items[MAX];
    int front;
    int rear;
};

// Function to initialize the deque
void initializeDeque(struct Deque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

// Check if the deque is full
int isFull(struct Deque* deque) {
    return ((deque->front == 0 && deque->rear == MAX - 1) || (deque->front == deque->rear + 1));
}

// Check if the deque is empty
int isEmpty(struct Deque* deque) {
    return (deque->front == -1);
}

// Insert at the front of the deque
void insertFront(struct Deque* deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full\n");
        return;
    }
    if (isEmpty(deque)) { // If the deque is empty
        deque->front = deque->rear = 0;
    } else if (deque->front == 0) { // If front is at the start
        deque->front = MAX - 1;
    } else {
        deque->front--;
    }
    deque->items[deque->front] = value;
    printf("Inserted %d at front\n", value);
}

// Insert at the rear of the deque
void insertRear(struct Deque* deque, int value) {
    if (isFull(deque)) {
        printf("Deque is full\n");
        return;
    }
    if (isEmpty(deque)) { // If the deque is empty
        deque->front = deque->rear = 0;
    } else if (deque->rear == MAX - 1) { // If rear is at the end
        deque->rear = 0;
    } else {
        deque->rear++;
    }
    deque->items[deque->rear] = value;
    printf("Inserted %d at rear\n", value);
}

// Delete from the front of the deque
int deleteFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int value = deque->items[deque->front];
    if (deque->front == deque->rear) { // If the deque becomes empty
        deque->front = deque->rear = -1;
    } else if (deque->front == MAX - 1) { // Wrap around
        deque->front = 0;
    } else {
        deque->front++;
    }
    printf("Deleted %d from front\n", value);
    return value;
}

// Delete from the rear of the deque
int deleteRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int value = deque->items[deque->rear];
    if (deque->front == deque->rear) { // If the deque becomes empty
        deque->front = deque->rear = -1;
    } else if (deque->rear == 0) { // Wrap around
        deque->rear = MAX - 1;
    } else {
        deque->rear--;
    }
    printf("Deleted %d from rear\n", value);
    return value;
}

// Display the elements of the deque
void displayDeque(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    int i = deque->front;
    while (1) {
        printf("%d ", deque->items[i]);
        if (i == deque->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Main function to demonstrate the deque operations
int main() {
    struct Deque deque;
    initializeDeque(&deque);

    insertRear(&deque, 10);
    insertRear(&deque, 20);
    insertFront(&deque, 5);
    displayDeque(&deque);

    deleteFront(&deque);
    displayDeque(&deque);

    insertRear(&deque, 30);
    insertFront(&deque, 2);
    displayDeque(&deque);

    deleteRear(&deque);
    displayDeque(&deque);

    return 0;
}
