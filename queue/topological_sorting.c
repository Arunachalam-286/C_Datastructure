#include <stdio.h>
#include <stdlib.h>

// Define the structure for an adjacency list node
typedef struct AdjListNode {
    int vertex;
    struct AdjListNode* next;
} AdjListNode;

// Define the structure for a graph
typedef struct Graph {
    int numVertices;
    AdjListNode** adjLists;
    int* inDegree;
} Graph;

// Define the structure for a queue
typedef struct Queue {
    int* items;
    int front;
    int rear;
    int size;
} Queue;

// Function to create a queue
Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    return queue;
}

// Check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == -1;
}

// Enqueue an element
void enqueue(Queue* queue, int value) {
    if (queue->rear == queue->size - 1) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1) queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Dequeue an element
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front >= queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return item;
}

// Function to create a graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (AdjListNode**)malloc(numVertices * sizeof(AdjListNode*));
    graph->inDegree = (int*)calloc(numVertices, sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    graph->inDegree[dest]++;
}

// Function for topological sorting
void topologicalSort(Graph* graph) {
    int numVertices = graph->numVertices;
    Queue* queue = createQueue(numVertices);
    int* topOrder = (int*)malloc(numVertices * sizeof(int));
    int index = 0;

    // Enqueue all vertices with in-degree 0
    for (int i = 0; i < numVertices; i++) {
        if (graph->inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }

    // Process the vertices in the queue
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        topOrder[index++] = current;

        // Reduce the in-degree of adjacent vertices
        AdjListNode* temp = graph->adjLists[current];
        while (temp) {
            graph->inDegree[temp->vertex]--;
            if (graph->inDegree[temp->vertex] == 0) {
                enqueue(queue, temp->vertex);
            }
            temp = temp->next;
        }
    }

    // Check if a topological order is possible
    if (index != numVertices) {
        printf("The graph has a cycle and cannot have a topological order.\n");
    } else {
        printf("Topological Order: ");
        for (int i = 0; i < index; i++) {
            printf("%d ", topOrder[i]);
        }
        printf("\n");
    }

    // Clean up
    free(queue->items);
    free(queue);
    free(topOrder);
}

// Main function
int main() {
    // Create a graph with 6 vertices
    Graph* graph = createGraph(6);

    // Add edges (tasks with dependencies)
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    // Perform topological sorting
    topologicalSort(graph);

    // Free graph memory
    for (int i = 0; i < graph->numVertices; i++) {
        AdjListNode* temp = graph->adjLists[i];
        while (temp) {
            AdjListNode* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjLists);
    free(graph->inDegree);
    free(graph);

    return 0;
}
