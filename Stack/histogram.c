#include <stdio.h>
#include <stdlib.h>

// Function to find the largest rectangular area in a histogram
int largestRectangleArea(int* heights, int n) {
    int* stack = (int*)malloc(n * sizeof(int)); // Stack to store indices
    int top = -1;                              // Initialize stack as empty
    int maxArea = 0;                           // Initialize max area as 0

    int i = 0;
    while (i < n) {
        // Push indices onto the stack if the stack is empty or heights are in increasing order
        if (top == -1 || heights[stack[top]] <= heights[i]) {
            stack[++top] = i++;
        } else {
            // Pop the top of the stack and calculate area
            int height = heights[stack[top--]];
            int width = (top == -1) ? i : (i - stack[top] - 1);
            int area = height * width;
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    // Process remaining elements in the stack
    while (top != -1) {
        int height = heights[stack[top--]];
        int width = (top == -1) ? i : (i - stack[top] - 1);
        int area = height * width;
        if (area > maxArea) {
            maxArea = area;
        }
    }

    free(stack);
    return maxArea;
}

// Main function to test the solution
int main() {
    int n;
    printf("Enter the number of bars in the histogram: ");
    scanf("%d", &n);

    int* heights = (int*)malloc(n * sizeof(int));
    printf("Enter the heights of the bars: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int maxArea = largestRectangleArea(heights, n);
    printf("The largest rectangular area in the histogram is: %d\n", maxArea);

    free(heights);
    return 0;
}
