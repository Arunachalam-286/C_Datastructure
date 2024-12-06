#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
    struct Node* random;
} Node;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = NULL;
    newNode->random = NULL;
    return newNode;
}

Node* cloneRecursive(Node* node, Node** visited) {
    if (!node) return NULL;

    if (visited[node->val]) return visited[node->val];

    Node* clonedNode = createNode(node->val);
    visited[node->val] = clonedNode;

    clonedNode->next = cloneRecursive(node->next, visited);
    clonedNode->random = cloneRecursive(node->random, visited);

    return clonedNode;
}

Node* cloneLinkedList(Node* head) {
    if (!head) return NULL;

    // Create an array to track visited nodes
    Node* visited[100] = {0};

    return cloneRecursive(head, visited);
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("Value: %d, Random: %d\n", current->val,
               current->random ? current->random->val : -1);
        current = current->next;
    }
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    head->random = head->next->next;  // 1 -> 3
    head->next->random = head;        // 2 -> 1
    head->next->next->random = head->next; // 3 -> 2

    Node* clonedList = cloneLinkedList(head);

    printf("Original List:\n");
    printList(head);

    printf("\nCloned List:\n");
    printList(clonedList);

    return 0;
}