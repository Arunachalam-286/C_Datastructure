#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
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

// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to swap two nodes in a linked list without swapping data
void swapNodes(struct Node** head, int x, int y) {
    if (x == y) return;  // No need to swap if the values are the same

    // Initialize pointers for the previous and current nodes
    struct Node *prevX = NULL, *currX = *head;
    struct Node *prevY = NULL, *currY = *head;

    // Search for x and y in the linked list
    while (currX != NULL && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }
    while (currY != NULL && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }

    // If either x or y is not present, return
    if (currX == NULL || currY == NULL) return;

    // If x is not the head node, update the previous node's next pointer
    if (prevX != NULL) {
        prevX->next = currY;
    } else {
        *head = currY;  // Make y the new head
    }

    // If y is not the head node, update the previous node's next pointer
    if (prevY != NULL) {
        prevY->next = currX;
    } else {
        *head = currX;  // Make x the new head
    }

    // Swap the next pointers of the two nodes
    struct Node* temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
}

// Main function to test the swapNodes function
int main() {
    struct Node* head = NULL;

    // Create a linked list: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 4);
    insertEnd(&head, 5);

    printf("Original Linked List: \n");
    printList(head);

    int x = 2, y = 4;  // Nodes to swap

    // Swap nodes with data x and y
    swapNodes(&head, x, y);
    
    printf("Linked List after swapping nodes with data %d and %d: \n", x, y);
    printList(head);

    return 0;
}