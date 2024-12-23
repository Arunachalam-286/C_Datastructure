#include <stdio.h>
#include <stdlib.h>

// Function to compare two integers for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Function to find the median in a sorted array
double findMedian(int* window, int size) {
    if (size % 2 == 0) {
        return (window[size / 2 - 1] + window[size / 2]) / 2.0;
    } else {
        return window[size / 2];
    }
}

// Function to insert an element into a sorted array
void insertSorted(int* window, int* size, int value) {
    window[*size] = value;
    (*size)++;
    qsort(window, *size, sizeof(int), compare);
}

// Function to remove an element from a sorted array
void removeElement(int* window, int* size, int value) {
    int i;
    for (i = 0; i < *size; i++) {
        if (window[i] == value) {
            break;
        }
    }
    for (; i < *size - 1; i++) {
        window[i] = window[i + 1];
    }
    (*size)--;
}

// Function to find the sliding window median
void slidingWindowMedian(int* nums, int numsSize, int k, double* result) {
    int* window = (int*)malloc(k * sizeof(int));
    int windowSize = 0;

    for (int i = 0; i < numsSize; i++) {
        // Add the new element to the window
        insertSorted(window, &windowSize, nums[i]);

        // Remove the element that is sliding out of the window
        if (i >= k) {
            removeElement(window, &windowSize, nums[i - k]);
        }

        // Calculate the median once the window is full
        if (i >= k - 1) {
            result[i - k + 1] = findMedian(window, windowSize);
        }
    }

    free(window);
}

// Main function to test the solution
int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3;
    double* result = (double*)malloc((numsSize - k + 1) * sizeof(double));

    slidingWindowMedian(nums, numsSize, k, result);

    printf("Sliding Window Median: ");
    for (int i = 0; i < numsSize - k + 1; i++) {
        printf("%.1f ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}
