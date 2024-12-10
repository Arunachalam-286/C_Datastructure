#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int getLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    int diff = abs(len1 - len2);

    struct Node* temp1 = head1;
    struct Node* temp2 = head2;

    if (len1 > len2) {
        for (int i = 0; i < diff; i++) {
            temp1 = temp1->next;
        }
    } else {
        for (int i = 0; i < diff; i++) {
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1 == temp2) {
            return temp1; 
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return NULL; 
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
    struct Node* head1 = createNode(1);
    head1->next = createNode(2);
    head1->next->next = createNode(3);
    head1->next->next->next = createNode(4);

    struct Node* head2 = createNode(5);
    head2->next = createNode(6);

    head2->next->next = head1->next->next; // Intersection at node 3

    struct Node* intersection = findIntersection(head1, head2);

    if (intersection != NULL) {
        printf("Intersection point: %d\n", intersection->data);
    } else {
        printf("No intersection point.\n");
    }

    return 0;
}