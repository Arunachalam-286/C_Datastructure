#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for the heap (max-heap or min-heap)
struct Heap {
    int items[MAX];
    int size;
};

// Initialize the heap
void initializeHeap(struct Heap* heap) {
    heap->size = 0;
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max-heapify
void maxHeapify(struct Heap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->items[left] > heap->items[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->items[right] > heap->items[largest]) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap->items[index], &heap->items[largest]);
        maxHeapify(heap, largest);
    }
}

// Min-heapify
void minHeapify(struct Heap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->items[left] < heap->items[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->items[right] < heap->items[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->items[index], &heap->items[smallest]);
        minHeapify(heap, smallest);
    }
}

// Insert an element into the max-heap
void insertMaxHeap(struct Heap* heap, int value) {
    if (heap->size >= MAX) {
        printf("Heap overflow\n");
        return;
    }

    heap->items[heap->size] = value;
    int index = heap->size;
    heap->size++;

    // Bubble up the inserted element to maintain max-heap property
    while (index > 0 && heap->items[(index - 1) / 2] < heap->items[index]) {
        swap(&heap->items[(index - 1) / 2], &heap->items[index]);
        index = (index - 1) / 2;
    }
}

// Insert an element into the min-heap
void insertMinHeap(struct Heap* heap, int value) {
    if (heap->size >= MAX) {
        printf("Heap overflow\n");
        return;
    }

    heap->items[heap->size] = value;
    int index = heap->size;
    heap->size++;

    // Bubble up the inserted element to maintain min-heap property
    while (index > 0 && heap->items[(index - 1) / 2] > heap->items[index]) {
        swap(&heap->items[(index - 1) / 2], &heap->items[index]);
        index = (index - 1) / 2;
    }
}

// Remove the maximum element from the max-heap
int removeMax(struct Heap* heap) {
    if (heap->size == 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int max = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return max;
}

// Remove the minimum element from the min-heap
int removeMin(struct Heap* heap) {
    if (heap->size == 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int min = heap->items[0];
    heap->items[0] = heap->items[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return min;
}

// Double-Ended Priority Queue structure
struct DEPriorityQueue {
    struct Heap maxHeap;
    struct Heap minHeap;
};

// Initialize the double-ended priority queue
void initializeDEPQ(struct DEPriorityQueue* depq) {
    initializeHeap(&depq->maxHeap);
    initializeHeap(&depq->minHeap);
}

// Insert an element into the double-ended priority queue
void insertDEPQ(struct DEPriorityQueue* depq, int value) {
    insertMaxHeap(&depq->maxHeap, value);
    insertMinHeap(&depq->minHeap, value);
}

// Remove and return the maximum element from the DEPQ
int removeMaxDEPQ(struct DEPriorityQueue* depq) {
    return removeMax(&depq->maxHeap);
}

// Remove and return the minimum element from the DEPQ
int removeMinDEPQ(struct DEPriorityQueue* depq) {
    return removeMin(&depq->minHeap);
}

// Main function to demonstrate the double-ended priority queue
int main() {
    struct DEPriorityQueue depq;
    initializeDEPQ(&depq);

    insertDEPQ(&depq, 10);
    insertDEPQ(&depq, 20);
    insertDEPQ(&depq, 15);
    insertDEPQ(&depq, 5);
    insertDEPQ(&depq, 30);

    printf("Max Element Removed: %d\n", removeMaxDEPQ(&depq)); // 30
    printf("Min Element Removed: %d\n", removeMinDEPQ(&depq)); // 5

    insertDEPQ(&depq, 25);
    printf("Max Element Removed: %d\n", removeMaxDEPQ(&depq)); // 25
    printf("Min Element Removed: %d\n", removeMinDEPQ(&depq)); // 10

    return 0;
}
