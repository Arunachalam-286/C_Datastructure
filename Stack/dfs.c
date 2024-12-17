#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

// Graph representation using adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

// Stack structure
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void dfs(Graph* graph, int startVertex);
Stack* createStack();
void push(Stack* stack, int value);
int pop(Stack* stack);
int isEmpty(Stack* stack);

int main() {
    int vertices = 6;  // Example graph with 6 vertices
    Graph* graph = createGraph(vertices);

    // Adding edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    printf("DFS Traversal starting from vertex 0:\n");
    dfs(graph, 0);

    return 0;
}

// Create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // For undirected graph, add an edge from dest to src as well
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// DFS function using a stack
void dfs(Graph* graph, int startVertex) {
    Stack* stack = createStack();
    push(stack, startVertex);

    while (!isEmpty(stack)) {
        int currentVertex = pop(stack);

        if (!graph->visited[currentVertex]) {
            printf("%d ", currentVertex);
            graph->visited[currentVertex] = 1;
        }

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                push(stack, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Create a stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Push an item onto the stack
void push(Stack* stack, int value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

// Pop an item from the stack
int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}
