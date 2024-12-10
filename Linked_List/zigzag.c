#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

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

void zigzagList(struct Node* head) {
    if (!head || !head->next) return;

    struct Node* current = head;
    int flag = 1; // 1 means '<', 0 means '>'

    while (current->next != NULL) {
        if (flag) { // "<" relation
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
            }
        } else { // ">" relation
            if (current->data < current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
            }
        }
        flag = !flag;
        current = current->next;
    }
}

int main() {
    struct Node* head = createNode(4);
    head->next = createNode(3);
    head->next->next = createNode(7);
    head->next->next->next = createNode(8);
    head->next->next->next->next = createNode(6);
    head->next->next->next->next->next = createNode(2);
    head->next->next->next->next->next->next = createNode(1);

    printf("Original List:\n");
    printList(head);

    zigzagList(head);

    printf("Zigzag List:\n");
    printList(head);

    return 0;
}
