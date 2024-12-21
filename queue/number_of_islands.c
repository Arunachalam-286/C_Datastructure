#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Direction vectors for moving up, down, left, and right
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};

// A structure to represent a point in the grid
typedef struct {
    int row, col;
} Point;

// A structure for a queue
typedef struct {
    Point* data;
    int front, rear, size, capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (Point*)malloc(capacity * sizeof(Point));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Function to enqueue a point
void enqueue(Queue* queue, int row, int col) {
    if (queue->size == queue->capacity) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear].row = row;
    queue->data[queue->rear].col = col;
    queue->size++;
}

// Function to dequeue a point
Point dequeue(Queue* queue) {
    Point frontPoint = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return frontPoint;
}

// Function to check if a cell is within bounds and unvisited land
bool isValid(int grid[MAX_ROWS][MAX_COLS], int rows, int cols, int row, int col, bool visited[MAX_ROWS][MAX_COLS]) {
    return row >= 0 && row < rows && col >= 0 && col < cols && grid[row][col] == 1 && !visited[row][col];
}

// BFS function to mark all land connected to (startRow, startCol) as visited
void bfs(int grid[MAX_ROWS][MAX_COLS], int rows, int cols, int startRow, int startCol, bool visited[MAX_ROWS][MAX_COLS]) {
    Queue* queue = createQueue(rows * cols);
    enqueue(queue, startRow, startCol);
    visited[startRow][startCol] = true;

    while (!isQueueEmpty(queue)) {
        Point current = dequeue(queue);
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + rowDir[i];
            int newCol = current.col + colDir[i];
            if (isValid(grid, rows, cols, newRow, newCol, visited)) {
                visited[newRow][newCol] = true;
                enqueue(queue, newRow, newCol);
            }
        }
    }

    free(queue->data);
    free(queue);
}

// Function to count the number of islands
int numIslands(int grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    bool visited[MAX_ROWS][MAX_COLS] = {false};
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                count++;
                bfs(grid, rows, cols, i, j, visited);
            }
        }
    }

    return count;
}

// Main function
int main() {
    int grid[MAX_ROWS][MAX_COLS] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };
    int rows = 4, cols = 5;

    printf("Number of Islands: %d\n", numIslands(grid, rows, cols));
    return 0;
}
