#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
    struct Node* child;
} Node;

// Function to flatten the multilevel doubly linked list
Node* flattenHelper(Node* head, Node** tail) {
    Node* current = head;

    while (current) {
        // Update the tail pointer
        *tail = current;

        // If the current node has a child
        if (current->child) {
            // Save the next node
            Node* nextNode = current->next;

            // Recursively flatten the child list
            Node* childTail = NULL;
            Node* childHead = flattenHelper(current->child, &childTail);

            // Connect current node to the child list
            current->next = childHead;
            childHead->prev = current;
            current->child = NULL;

            // Connect the end of the child list to the next node
            if (nextNode) {
                childTail->next = nextNode;
                nextNode->prev = childTail;
            }

            // Update the tail pointer
            *tail = childTail;
            current = nextNode;
        } else {
            current = current->next;
        }
    }

    return head;
}

Node* flatten(Node* head) {
    Node* tail = NULL;
    return flattenHelper(head, &tail);
}

// Helper function to create a new node
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->child = NULL;
    return newNode;
}

// Helper function to print the list
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

// Test the flatten function
int main() {
    // Create nodes
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->prev = head;

    head->next->child = createNode(3);

    head->next->next = createNode(4);
    head->next->next->prev = head->next;

    // Flatten the list
    Node* flattenedHead = flatten(head);

    // Print the flattened list
    printList(flattenedHead);

    return 0;
}