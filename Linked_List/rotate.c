#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode; 
    return newNode;
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        
        while (temp->next != *head) {
            temp = temp->next;
        }
        
        temp->next = newNode;
        newNode->next = *head;
    }
}

void printList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    
    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("...\n");
}

void splitCircularList(struct Node* head, struct Node** head1, struct Node** head2) {
    if (head == NULL) {
        return;
    }
    
    struct Node* slow = head;
    struct Node* fast = head;
    
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    *head1 = head;               
    *head2 = slow->next;         
    slow->next = head;           
    
    struct Node* temp = *head2;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = *head2;
}

int main() {
    struct Node* head = NULL;
    
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 4);
    insertEnd(&head, 5);
    
    printf("Original Circular Linked List: \n");
    printList(head);

    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    splitCircularList(head, &head1, &head2);
    
    printf("First Half: \n");
    printList(head1);
    
    printf("Second Half: \n");
    printList(head2);
    
    return 0;
}