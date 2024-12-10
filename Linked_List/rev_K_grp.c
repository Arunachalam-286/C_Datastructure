#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* reverseKGroup(Node* head, int k) {
    if (!head || k == 1) return head;

    Node* temp = head;
    int count = 0;
    while (temp) {
        count++;
        temp = temp->next;
    }

    Node* dummy = createNode(0);
    dummy->next = head;

    Node *prev = dummy, *curr = dummy, *next = dummy;
    while (count >= k) {
        curr = prev->next;
        next = curr->next;

        for (int i = 1; i < k; i++) {
            curr->next = next->next;
            next->next = prev->next;
            prev->next = next;
            next = curr->next;
        }

        prev = curr;
        count -= k;
    }

    return dummy->next;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original List:\n");
    printList(head);

    int k = 3;
    head = reverseKGroup(head, k);

    printf("\nList after reversing in groups of %d:\n", k);
    printList(head);

    return 0;
}