#include <stdio.h>
#include <stdlib.h>

// Definition of a circular linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a circular linked list of size n
struct Node* createCircularList(int n) {
    if (n <= 0) {
        return NULL;
    }

    struct Node* head = createNode(1);
    struct Node* prev = head;

    for (int i = 2; i <= n; i++) {
        struct Node* newNode = createNode(i);
        prev->next = newNode;
        prev = newNode;
    }
    prev->next = head; // Make the list circular
    return head;
}

// Function to solve the Josephus problem
int josephus(struct Node* head, int k) {
    if (head == NULL || k <= 0) {
        return -1; // Invalid input
    }

    struct Node* current = head;
    struct Node* prev = NULL;

    // Loop until only one node is left
    while (current->next != current) {
        // Traverse k-1 nodes
        for (int i = 1; i < k; i++) {
            prev = current;
            current = current->next;
        }

        // Remove the k-th node
        prev->next = current->next;
        printf("Person %d is eliminated\n", current->data);
        free(current);
        current = prev->next;
    }

    // The last remaining node
    int survivor = current->data;
    free(current); // Clean up the last node
    return survivor;
}

// Example usage
int main() {
    int n = 7; // Number of people
    int k = 3; // Step size

    struct Node* head = createCircularList(n);

    int survivor = josephus(head, k);
    printf("The survivor is person %d\n", survivor);

    return 0;
}