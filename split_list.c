#include <stdio.h>
#include <stdlib.h>

// Node structure for singly linked list
struct ListNode {
    int data;
    struct ListNode* next;
};

// Function to create a new node
struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node at the end of the list
void append(struct ListNode** head, int data) {
    struct ListNode* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to split the linked list into k parts
struct ListNode** splitList(struct ListNode* head, int k, int* returnSize) {
    struct ListNode** result = (struct ListNode*)malloc(k * sizeof(struct ListNode));
    *returnSize = 0;

    if (head == NULL) {
        for (int i = 0; i < k; i++) {
            result[i] = NULL;
        }
        return result;
    }

    // Calculate the length of the linked list
    int length = 0;
    struct ListNode* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    // Calculate the size of each part
    int partSize = length / k;
    int extraNodes = length % k;

    // Split the list into k parts
    struct ListNode* current = head;
    for (int i = 0; i < k; i++) {
        result[i] = current;
        int currentPartSize = partSize + (i < extraNodes ? 1 : 0);
        for (int j = 0; j < currentPartSize - 1; j++) {
            if (current != NULL) {
                current = current->next;
            }
        }

        // If there are more nodes, disconnect the current part
        if (current != NULL) {
            struct ListNode* temp = current;
            current = current->next;
            temp->next = NULL;
        }
        
        (*returnSize)++;
    }

    return result;
}

// Function to print the result of the split
void printSplit(struct ListNode** result, int k, int returnSize) {
    for (int i = 0; i < returnSize; i++) {
        printf("Part %d: ", i + 1);
        printList(result[i]);
    }
    for (int i = returnSize; i < k; i++) {
        printf("Part %d: NULL\n", i + 1);
    }
}

// Main function to test the splitList function
int main() {
    struct ListNode* head = NULL;

    // Create a linked list
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);
    append(&head, 7);
    append(&head, 8);
    append(&head, 9);
    append(&head, 10);

    printf("Original Linked List: ");
    printList(head);

    int k = 3;  // Number of parts to split into
    int returnSize = 0;

    struct ListNode** result = splitList(head, k, &returnSize);

    printf("\nSplit Linked List into %d parts:\n", k);
    printSplit(result, k, returnSize);

    // Free the allocated memory for result
    free(result);

    return 0;
}