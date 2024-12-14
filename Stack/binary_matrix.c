#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Function to find the maximum area of a histogram using a stack
int maxHistogramArea(int* heights, int n) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;  // Stack is empty
    int maxArea = 0;
    int i = 0;

    while (i < n) {
        // Push current index if the stack is empty or the height is increasing
        if (top == -1 || heights[stack[top]] <= heights[i]) {
            stack[++top] = i++;
        } else {
            // Pop the stack and calculate the area with the popped height
            int h = heights[stack[top--]];
            int width = (top == -1) ? i : i - stack[top] - 1;
            maxArea = (maxArea > h * width) ? maxArea : h * width;
        }
    }

    // Process remaining bars in the stack
    while (top != -1) {
        int h = heights[stack[top--]];
        int width = (top == -1) ? i : i - stack[top] - 1;
        maxArea = (maxArea > h * width) ? maxArea : h * width;
    }

    free(stack);
    return maxArea;
}

// Function to find the largest rectangle in a binary matrix
int maximalRectangle(int** matrix, int rows, int cols) {
    if (rows == 0 || cols == 0) return 0;

    int* heights = (int*)calloc(cols, sizeof(int));
    int maxArea = 0;

    for (int i = 0; i < rows; i++) {
        // Update the histogram heights for the current row
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                heights[j] = 0;
            } else {
                heights[j] += 1;
            }
        }

        // Compute the maximum area for the current histogram
        int currentMaxArea = maxHistogramArea(heights, cols);
        maxArea = (maxArea > currentMaxArea) ? maxArea : currentMaxArea;
    }

    free(heights);
    return maxArea;
}

// Main function to test the solution
int main() {
    int rows = 4, cols = 5;
    int* matrixData[] = {
        (int[]){1, 0, 1, 0, 0},
        (int[]){1, 0, 1, 1, 1},
        (int[]){1, 1, 1, 1, 1},
        (int[]){1, 0, 0, 1, 0}
    };

    // Convert to dynamic 2D array
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = matrixData[i];
    }

    int maxRectangle = maximalRectangle(matrix, rows, cols);
    printf("The largest rectangle area is: %d\n", maxRectangle);

    free(matrix);
    return 0;
}
