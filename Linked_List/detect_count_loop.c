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

int detectAndCountLoop(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            int loopLength = 1;
            Node* temp = slow;

            while (temp->next != slow) {
                loopLength++;
                temp = temp->next;
            }

            return loopLength;
        }
    }

    return 0;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    head->next->next->next->next->next = head->next->next;

    int loopLength = detectAndCountLoop(head);

    if (loopLength > 0) {
        printf("Loop detected with length: %d\n", loopLength);
    } else {
        printf("No loop detected.\n");
    }

    return 0;
}