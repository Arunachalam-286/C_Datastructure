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

Node* findMiddle(Node* head) {
    if (!head) return NULL;
    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->data <= right->data) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* middle = findMiddle(head);
    Node* left = head;
    Node* right = middle->next;
    middle->next = NULL;  
    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(3);

    printf("Original List:\n");
    printList(head);

    head = mergeSort(head);

    printf("\nSorted List:\n");
    printList(head);

    return 0;
}