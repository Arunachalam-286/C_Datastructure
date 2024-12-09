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

// Function to reverse the first k nodes of the linked list
struct Node* reverseKNodes(struct Node* head, int k) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    int count = 0;

    // Reverse the first k nodes
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    // The head node becomes the tail after reversing
    head->next = current;

    return prev;
}

// Function to reverse alternate k nodes in a linked list
struct Node* reverseAlternateKNodes(struct Node* head, int k) {
    if (!head || k <= 0) {
        return head;
    }

    struct Node* current = head;
    struct Node* prev = NULL;
    int toggle = 1; // 1: reverse, 0: skip

    while (current != NULL) {
        if (toggle) {
            // Reverse the next k nodes
            struct Node* start = current;
            struct Node* reversed = reverseKNodes(current, k);

            if (prev) {
                prev->next = reversed;
            } else {
                head = reversed;
            }

            // Move the previous pointer to the end of the reversed segment
            prev = start;
            current = start->next;
        } else {
            // Skip the next k nodes
            int count = 0;
            while (current != NULL && count < k) {
                prev = current;
                current = current->next;
                count++;
            }
        }

        toggle = !toggle; // Toggle the operation
    }

    return head;
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Example usage
int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);
    head->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next = createNode(8);
    head->next->next->next->next->next->next->next->next = createNode(9);

    int k = 3;

    printf("Original List: ");
    printList(head);

    head = reverseAlternateKNodes(head, k);

    printf("Modified List: ");
    printList(head);

    return 0;
}