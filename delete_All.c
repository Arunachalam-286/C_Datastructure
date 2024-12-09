#include <stdio.h>
#include <stdlib.h>

// Definition of a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Helper function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to delete all occurrences of a given key in the linked list
struct Node* deleteKey(struct Node* head, int key) {
    struct Node* temp = head;
    struct Node* prev = NULL;

    // Remove nodes with the key at the head
    while (temp != NULL && temp->data == key) {
        head = temp->next; // Move the head
        free(temp);        // Free the old head
        temp = head;       // Update temp
    }

    // Traverse the rest of the list
    while (temp != NULL) {
        // If the current node has the key
        if (temp->data == key) {
            prev->next = temp->next; // Unlink the node
            free(temp);              // Free the memory
            temp = prev->next;       // Move to the next node
        } else {
            prev = temp;             // Update previous node
            temp = temp->next;       // Move to the next node
        }
    }

    return head;
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Example usage
int main() {
    // Create a linked list: 1 -> 2 -> 3 -> 2 -> 4 -> 2
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(2);

    printf("Original list: ");
    printList(head);

    int key = 2;
    head = deleteKey(head, key);

    printf("Modified list after deleting %d: ", key);
    printList(head);

    return 0;
}