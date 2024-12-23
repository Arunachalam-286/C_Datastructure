#include <stdio.h>
#include <stdlib.h>

// Define directions for moving in the grid (up, down, left, right)
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};

// Structure to represent a point in the grid
typedef struct {
    int x, y, distance;
} Point;

// Queue structure for BFS
typedef struct {
    Point* data;
    int front, rear, capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (Point*)malloc(capacity * sizeof(Point));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return queue->front > queue->rear;
}

// Function to enqueue a point
void enqueue(Queue* queue, Point p) {
    if (queue->rear + 1 < queue->capacity) {
        queue->data[++queue->rear] = p;
    }
}

// Function to dequeue a point
Point dequeue(Queue* queue) {
    return queue->data[queue->front++];
}

// Function to check if a cell is valid to visit
int isValid(int x, int y, int rows, int cols, int** maze, int** visited) {
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y];
}

// Function to find the shortest path in the maze using BFS
int shortestPathInMaze(int** maze, int rows, int cols, int sx, int sy, int dx, int dy) {
    // Edge case: Start or destination is blocked
    if (maze[sx][sy] == 1 || maze[dx][dy] == 1) {
        return -1;
    }

    // Create a queue for BFS
    Queue* queue = createQueue(rows * cols);

    // Create a visited array
    int** visited = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)calloc(cols, sizeof(int));
    }

    // Enqueue the starting point and mark it as visited
    enqueue(queue, (Point){sx, sy, 0});
    visited[sx][sy] = 1;

    // Perform BFS
    while (!isEmpty(queue)) {
        Point current = dequeue(queue);

        // If we reach the destination, return the distance
        if (current.x == dx && current.y == dy) {
            return current.distance;
        }

        // Explore all possible directions
        for (int i = 0; i < 4; i++) {
            int newX = current.x + rowDir[i];
            int newY = current.y + colDir[i];

            if (isValid(newX, newY, rows, cols, maze, visited)) {
                enqueue(queue, (Point){newX, newY, current.distance + 1});
                visited[newX][newY] = 1;
            }
        }
    }

    // If we exhaust the queue without finding the destination, return -1
    return -1;
}

// Main function to test the shortestPathInMaze function
int main() {
    int rows = 5, cols = 5;

    // Define a maze
    int mazeData[5][5] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    // Convert mazeData to a dynamic 2D array
    int** maze = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        maze[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            maze[i][j] = mazeData[i][j];
        }
    }

    // Define start and destination points
    int sx = 0, sy = 0;
    int dx = 4, dy = 4;

    // Find the shortest path
    int result = shortestPathInMaze(maze, rows, cols, sx, sy, dx, dy);

    if (result != -1) {
        printf("The shortest path from (%d, %d) to (%d, %d) is %d steps.\n", sx, sy, dx, dy, result);
    } else {
        printf("No path exists from (%d, %d) to (%d, %d).\n", sx, sy, dx, dy);
    }

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
