#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};


int countNodes(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


int main() {
    
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    
    int nodeCount = countNodes(head);
    printf("Number of nodes in the linked list: %d\n", nodeCount);

    
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}