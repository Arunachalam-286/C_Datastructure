#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};


void findNthFromEnd(struct Node* head, int n) {
    struct Node* first = head;
    struct Node* second = head;

    
    for (int i = 0; i < n; i++) {
        if (first == NULL) {
            printf("The list has fewer than %d nodes.\n", n);
            return;
        }
        first = first->next;
    }

    
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    
    printf("The %d-th node from the end is: %d\n", n, second->data);
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
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);

    
    int n = 2;
    findNthFromEnd(head, n);

    
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
