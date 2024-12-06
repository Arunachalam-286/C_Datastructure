#include <stdio.h>
#include <stdlib.h>

// Node structure
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

// Function to check if the list is circular
int isCircular(struct Node* head) {
    if (head == NULL) {
        return 1; // An empty list is considered circular
    }

    struct Node* temp = head->next;

    // Traverse the list and check if we come back to the head
    while (temp != NULL && temp != head) {
        temp = temp->next;
    }

    return (temp == head); // If temp becomes head, the list is circular
}

// Function to print the result
void printResult(int isCircular) {
    if (isCircular) {
        printf("The linked list is circular.\n");
    } else {
        printf("The linked list is not circular.\n");
    }
}

// Main function
int main() {
    // Create a non-circular linked list
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = NULL;

    // Check if the list is circular
    printResult(isCircular(head));

    // Create a circular linked list
    struct Node* circularHead = createNode(1);
    circularHead->next = createNode(2);
    circularHead->next->next = createNode(3);
    circularHead->next->next->next = circularHead; // Makes the list circular

    // Check if the circular list is circular
    printResult(isCircular(circularHead));

    return 0;
}