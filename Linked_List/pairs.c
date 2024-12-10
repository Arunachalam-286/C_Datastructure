#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtTail(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to print the list
void printList(struct Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to find pairs with a given sum
void findPairs(struct Node* head, int target) {
    struct Node* start = head;
    struct Node* end = head;

    // Move 'end' to the last node
    while (end->next != NULL) {
        end = end->next;
    }

    int found = 0;
    printf("Pairs with sum %d:\n", target);
    while (start != NULL && end != NULL && start != end && end->next != start) {
        int sum = start->data + end->data;

        if (sum == target) {
            printf("(%d, %d)\n", start->data, end->data);
            found = 1;
            start = start->next;
            end = end->prev;
        } else if (sum < target) {
            start = start->next;
        } else {
            end = end->prev;
        }
    }

    if (!found) {
        printf("No pairs found.\n");
    }
}

// Main function
int main() {
    struct Node* head = NULL;

    // Insert nodes into the list
    insertAtTail(&head, 1);
    insertAtTail(&head, 2);
    insertAtTail(&head, 4);
    insertAtTail(&head, 5);
    insertAtTail(&head, 6);
    insertAtTail(&head, 8);
    insertAtTail(&head, 9);

    // Print the list
    printList(head);

    // Find pairs with a given sum
    int target = 10;
    findPairs(head, target);

    return 0;
}