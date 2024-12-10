#include <stdio.h>
#include <stdlib.h>

// Definition of a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Helper function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to merge two sorted linked lists
struct Node* mergeTwoLists(struct Node* l1, struct Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    struct Node* result;
    if (l1->data < l2->data) {
        result = l1;
        result->next = mergeTwoLists(l1->next, l2);
    } else {
        result = l2;
        result->next = mergeTwoLists(l1, l2->next);
    }
    return result;
}

// Function to merge k sorted linked lists using divide and conquer
struct Node* mergeKLists(struct Node** lists, int start, int end) {
    if (start > end) return NULL;
    if (start == end) return lists[start];

    int mid = start + (end - start) / 2;

    struct Node* left = mergeKLists(lists, start, mid);
    struct Node* right = mergeKLists(lists, mid + 1, end);

    return mergeTwoLists(left, right);
}

// Function to print a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Example usage
int main() {
    // Create 3 sorted linked lists
    struct Node* list1 = createNode(1);
    list1->next = createNode(4);
    list1->next->next = createNode(5);

    struct Node* list2 = createNode(1);
    list2->next = createNode(3);
    list2->next->next = createNode(4);

    struct Node* list3 = createNode(2);
    list3->next = createNode(6);

    struct Node* lists[] = {list1, list2, list3};
    int k = 3;

    struct Node* result = mergeKLists(lists, 0, k - 1);

    printf("Merged list: ");
    printList(result);

    return 0;
}