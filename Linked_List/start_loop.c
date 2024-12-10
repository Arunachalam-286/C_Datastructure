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

struct Node* findLoopStart(struct Node* head) {
    struct Node *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            break;
        }
    }

    if (fast == NULL || fast->next == NULL) {
        return NULL;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow; 
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    head->next->next->next->next->next = head->next->next;

    struct Node* loopStart = findLoopStart(head);
    if (loopStart != NULL) {
        printf("Loop starts at node with data: %d\n", loopStart->data);
    } else {
        printf("No loop detected in the linked list.\n");
    }

    return 0;
}
