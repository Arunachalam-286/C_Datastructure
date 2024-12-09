#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the linked list
struct Node {
    int data;
    struct Node* next;
    struct Node* child;
};

// Helper function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->child = NULL;
    return newNode;
}

// Function to merge two sorted linked lists
struct Node* mergeTwoLists(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    struct Node* result;
    if (a->data < b->data) {
        result = a;
        result->child = mergeTwoLists(a->child, b);
    } else {
        result = b;
        result->child = mergeTwoLists(a, b->child);
    }
    return result;
}

// Function to flatten the sorted linked list
struct Node* flattenList(struct Node* head) {
    if (!head || !head->next) {
        return head;
    }

    // Recursively flatten the next part of the list
    head->next = flattenList(head->next);

    // Merge the current list with the flattened next part
    head = mergeTwoLists(head, head->next);

    return head;
}

// Function to print the flattened linked list
void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->child;
    }
    printf("\n");
}

// Example usage
int main() {
    struct Node* head = createNode(5);
    head->child = createNode(7);
    head->child->child = createNode(8);
    head->child->child->child = createNode(30);

    head->next = createNode(10);
    head->next->child = createNode(20);

    head->next->next = createNode(19);
    head->next->next->child = createNode(22);
    head->next->next->child->child = createNode(50);

    head->next->next->next = createNode(28);
    head->next->next->next->child = createNode(35);
    head->next->next->next->child->child = createNode(40);
    head->next->next->next->child->child->child = createNode(45);

    head = flattenList(head);
    printList(head);

    return 0;
}