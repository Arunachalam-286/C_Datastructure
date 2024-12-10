#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};


void detectAndRemoveLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;

    
    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        
        if (slow == fast) {
            printf("Loop detected.\n");
            
            removeLoop(slow, head);
            return;
        }
    }
    printf("No loop detected.\n");
}


void removeLoop(struct Node* loopNode, struct Node* head) {
    struct Node* ptr1 = head;
    struct Node* ptr2;

    while (1) {
        ptr2 = loopNode;

        
        while (ptr2->next != loopNode && ptr2->next != ptr1) {
            ptr2 = ptr2->next;
        }

        
        if (ptr2->next == ptr1) {
            break;
        }

        ptr1 = ptr1->next;
    }

    
    ptr2->next = NULL;
    printf("Loop removed.\n");
}


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    
    head->next->next->next->next->next = head->next; 
    
    detectAndRemoveLoop(head);

    printf("Linked List after removing loop: \n");
    printList(head);

    return 0;
}
