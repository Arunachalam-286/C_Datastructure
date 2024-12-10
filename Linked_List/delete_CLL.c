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

// Function to insert a node at the end of a circular linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        newNode->next = newNode; // Point to itself
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = *head;
}

// Function to delete the k-th node from the circular linked list
void deleteKthNode(struct Node** head, int k) {
    if (*head == NULL) {
        printf("The list is empty. Cannot delete node.\n");
        return;
    }

    struct Node* current = *head;
    struct Node* prev = NULL;

    // If k is 1, delete the head node
    if (k == 1) {
        // Find the last node
        while (current->next != *head) {
            current = current->next;
        }

        // If there's only one node in the list
        if (current == *head) {
            free(*head);
            *head = NULL;
            return;
        }

        // Update the last node's next pointer and delete the head
        current->next = (*head)->next;
        free(*head);
        *head = current->next;
        return;
    }

    // Traverse to the k-th node
    current = *head;
    for (int i = 1; i < k; i++) {
        prev = current;
        current = current->next;

        // If we looped through the entire list and didn't find the k-th node
        if (current == *head) {
            printf("Invalid value of k. Node does not exist.\n");
            return;
        }
    }

    // Delete the k-th node
    prev->next = current->next;
    free(current);
}

// Function to display the circular linked list
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insert nodes
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);
    displayList(head);

    // Delete the 1st node (head)
    printf("Deleting the 1st node:\n");
    deleteKthNode(&head, 1);
    displayList(head);

    // Delete the 2nd node
    printf("Deleting the 2nd node:\n");
    deleteKthNode(&head, 2);
    displayList(head);

    // Delete an invalid node
    printf("Deleting the 5th node (invalid):\n");
    deleteKthNode(&head, 5);

    // Delete remaining nodes
    printf("Deleting the remaining nodes:\n");
    deleteKthNode(&head, 1);
    deleteKthNode(&head, 1);
    displayList(head);

    return 0;
}