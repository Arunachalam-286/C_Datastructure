#include <stdio.h>
#include <stdlib.h>

// Define directions for moving in the grid (up, down, left, right)
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};

// Structure to represent a cell in the grid
typedef struct {
    int x, y, time;
} Cell;

// Queue structure for BFS
typedef struct {
    Cell* data;
    int front, rear, capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (Cell*)malloc(capacity * sizeof(Cell));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front > queue->rear;
}

// Function to enqueue a cell
void enqueue(Queue* queue, Cell cell) {
    if (queue->rear + 1 < queue->capacity) {
        queue->data[++queue->rear] = cell;
    }
}

// Function to dequeue a cell
Cell dequeue(Queue* queue) {
    return queue->data[queue->front++];
}

// Function to check if a cell is valid
int isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Function to find the minimum time to rot all oranges
int orangesRotting(int** grid, int rows, int cols) {
    Queue* queue = createQueue(rows * cols);
    int freshCount = 0, timeElapsed = 0;

    // Initialize the queue with all initially rotten oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) {
                enqueue(queue, (Cell){i, j, 0}); // Add rotten orange with time 0
            } else if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    // Perform BFS
    while (!isEmpty(queue)) {
        Cell current = dequeue(queue);

        // Update the maximum time elapsed
        timeElapsed = current.time;

        // Try to rot adjacent fresh oranges
        for (int i = 0; i < 4; i++) {
            int newX = current.x + rowDir[i];
            int newY = current.y + colDir[i];

            if (isValid(newX, newY, rows, cols) && grid[newX][newY] == 1) {
                grid[newX][newY] = 2; // Mark orange as rotten
                freshCount--;        // Decrease fresh count
                enqueue(queue, (Cell){newX, newY, current.time + 1});
            }
        }
    }

    // If there are still fresh oranges left, return -1
    if (freshCount > 0) {
        return -1;
    }

    return timeElapsed;
}

// Main function to test the solution
int main() {
    int rows = 3, cols = 3;

    // Define a grid
    int gridData[3][3] = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    // Convert gridData to a dynamic 2D array
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            grid[i][j] = gridData[i][j];
        }
    }

    // Find the minimum time to rot all oranges
    int result = orangesRotting(grid, rows, cols);

    if (result != -1) {
        printf("Minimum time to rot all oranges: %d\n", result);
    } else {
        printf("Not all oranges can rot.\n");
    }

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
