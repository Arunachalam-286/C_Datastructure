#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node {
    int data;
    struct Node* next;
};


bool search(struct Node* head, int key) {
    struct Node* current = head;

    
    while (current != NULL) {
        if (current->data == key) {
            return true; 
        }
        current = current->next;
    }
    return false; 
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

    
    int key = 20;

    
    if (search(head, key)) {
        printf("Value %d found in the linked list.\n", key);
    } else {
        printf("Value %d not found in the linked list.\n", key);
    }

    
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}