#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for the priority queue (min-heap)
typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    MinHeapNode* nodes;
    int* position;
    int size;
    int capacity;
} MinHeap;

// Create a new MinHeapNode
MinHeapNode createNode(int vertex, int distance) {
    MinHeapNode node;
    node.vertex = vertex;
    node.distance = distance;
    return node;
}

// Create a MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->nodes = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    minHeap->position = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// Swap two MinHeapNodes
void swapNodes(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify a subtree with root at index `idx`
void heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->nodes[left].distance < minHeap->nodes[smallest].distance) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->nodes[right].distance < minHeap->nodes[smallest].distance) {
        smallest = right;
    }

    if (smallest != idx) {
        // Swap nodes
        MinHeapNode smallestNode = minHeap->nodes[smallest];
        MinHeapNode idxNode = minHeap->nodes[idx];

        // Update positions
        minHeap->position[smallestNode.vertex] = idx;
        minHeap->position[idxNode.vertex] = smallest;

        swapNodes(&minHeap->nodes[smallest], &minHeap->nodes[idx]);
        heapify(minHeap, smallest);
    }
}

// Extract the node with the smallest distance
MinHeapNode extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        return createNode(-1, INT_MAX);
    }

    MinHeapNode root = minHeap->nodes[0];
    MinHeapNode lastNode = minHeap->nodes[minHeap->size - 1];
    minHeap->nodes[0] = lastNode;

    minHeap->position[root.vertex] = -1;
    minHeap->position[lastNode.vertex] = 0;

    minHeap->size--;
    heapify(minHeap, 0);

    return root;
}

// Decrease the distance of a given vertex
void decreaseKey(MinHeap* minHeap, int vertex, int distance) {
    int idx = minHeap->position[vertex];
    minHeap->nodes[idx].distance = distance;

    while (idx > 0 && minHeap->nodes[idx].distance < minHeap->nodes[(idx - 1) / 2].distance) {
        // Swap with parent
        MinHeapNode currentNode = minHeap->nodes[idx];
        MinHeapNode parentNode = minHeap->nodes[(idx - 1) / 2];

        minHeap->position[currentNode.vertex] = (idx - 1) / 2;
        minHeap->position[parentNode.vertex] = idx;

        swapNodes(&minHeap->nodes[idx], &minHeap->nodes[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Check if a vertex is in the min heap
int isInMinHeap(MinHeap* minHeap, int vertex) {
    return minHeap->position[vertex] < minHeap->size;
}

// Dijkstra's algorithm to find the shortest path from a source vertex
void dijkstra(int** graph, int V, int src) {
    int* dist = (int*)malloc(V * sizeof(int));

    // Create a min heap
    MinHeap* minHeap = createMinHeap(V);

    // Initialize distances and min heap
    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        minHeap->nodes[v] = createNode(v, dist[v]);
        minHeap->position[v] = v;
    }

    // Set the distance of the source vertex to 0
    dist[src] = 0;
    minHeap->nodes[src] = createNode(src, dist[src]);
    minHeap->position[src] = src;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    // Process the graph
    while (minHeap->size > 0) {
        MinHeapNode minNode = extractMin(minHeap);
        int u = minNode.vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }

    // Print the result
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }

    free(dist);
    free(minHeap->nodes);
    free(minHeap->position);
    free(minHeap);
}

// Main function to test the solution
int main() {
    int V = 5;
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }

    // Example graph
    int exampleGraph[5][5] = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}};

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = exampleGraph[i][j];
        }
    }

    dijkstra(graph, V, 0);

    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
