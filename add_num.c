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

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

Node* addTwoNumbers(Node* l1, Node* l2) {
    Node* result = NULL;
    Node* tail = NULL;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }

        carry = sum / 10;
        int digit = sum % 10;

        if (result == NULL) {
            result = createNode(digit);
            tail = result;
        } else {
            tail->next = createNode(digit);
            tail = tail->next;
        }
    }

    return result;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* l1 = NULL;
    appendNode(&l1, 2);
    appendNode(&l1, 4);
    appendNode(&l1, 3);

    Node* l2 = NULL;
    appendNode(&l2, 5);
    appendNode(&l2, 6);
    appendNode(&l2, 4);

    printf("First Number: ");
    printList(l1);

    printf("Second Number: ");
    printList(l2);

    Node* result = addTwoNumbers(l1, l2);

    printf("Result: ");
    printList(result);

    return 0;
}
