#include <stdio.h>
#include <stdlib.h>

// Function to find the first negative integer in every window of size k
void findFirstNegative(int arr[], int n, int k) {
    int* queue = (int*)malloc(n * sizeof(int)); // Array to act as the queue
    int front = 0, rear = 0;                   // Queue pointers

    // Iterate through the array
    for (int i = 0; i < n; i++) {
        // Add current element's index to the queue if it's negative
        if (arr[i] < 0) {
            queue[rear++] = i;
        }

        // Remove elements from the front that are out of the current window
        if (front < rear && queue[front] < i - k + 1) {
            front++;
        }

        // If the window is valid (i >= k - 1), print the result
        if (i >= k - 1) {
            if (front < rear) {
                printf("%d ", arr[queue[front]]); // First negative integer
            } else {
                printf("0 "); // No negative integer in this window
            }
        }
    }

    // Free the queue memory
    free(queue);
}

// Main function
int main() {
    int arr[] = {12, -1, -7, 8, -15, 30, 16, 28};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("First Negative Integer in every Window of Size %d:\n", k);
    findFirstNegative(arr, n, k);

    return 0;
}
