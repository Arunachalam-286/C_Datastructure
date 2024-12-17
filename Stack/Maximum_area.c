#include <stdio.h>

#define MAX_ROW 50
#define MAX_COL 50

// Define a structure for stack elements to store coordinates
typedef struct {
    int x;
    int y;
} Point;

// Stack implementation for DFS
typedef struct {
    Point data[MAX_ROW * MAX_COL];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Push a point onto the stack
void push(Stack *s, int x, int y) {
    s->data[++(s->top)] = (Point){x, y};
}

// Pop a point from the stack
Point pop(Stack *s) {
    return s->data[(s->top)--];
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if a position is valid in the grid
int isValid(int x, int y, int rows, int cols, int grid[MAX_ROW][MAX_COL], int visited[MAX_ROW][MAX_COL]) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && !visited[x][y]);
}

// Perform DFS using a stack to calculate the area of an island
int dfs(int grid[MAX_ROW][MAX_COL], int visited[MAX_ROW][MAX_COL], int startX, int startY, int rows, int cols) {
    // Initialize stack
    Stack stack;
    initStack(&stack);
    push(&stack, startX, startY);

    // Directions: up, down, left, right
    int dirX[] = {-1, 1, 0, 0};
    int dirY[] = {0, 0, -1, 1};

    int area = 0;

    while (!isEmpty(&stack)) {
        Point current = pop(&stack);

        int x = current.x;
        int y = current.y;

        // Skip if already visited
        if (visited[x][y]) continue;

        // Mark the current cell as visited
        visited[x][y] = 1;
        area++;

        // Explore all 4 possible directions
        for (int i = 0; i < 4; i++) {
            int newX = x + dirX[i];
            int newY = y + dirY[i];

            if (isValid(newX, newY, rows, cols, grid, visited)) {
                push(&stack, newX, newY);
            }
        }
    }

    return area;
}

// Find the maximum area of an island
int maxAreaOfIsland(int grid[MAX_ROW][MAX_COL], int rows, int cols) {
    int visited[MAX_ROW][MAX_COL] = {0}; // Initialize visited grid with 0
    int maxArea = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                int area = dfs(grid, visited, i, j, rows, cols);
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }

    return maxArea;
}

int main() {
    int grid[MAX_ROW][MAX_COL] = {
        {0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}
    };

    int rows = 4, cols = 6;

    int maxArea = maxAreaOfIsland(grid, rows, cols);
    printf("The maximum area of an island is: %d\n", maxArea);

    return 0;
}
