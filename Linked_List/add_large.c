#include <stdio.h>
#include <stdlib.h>

// Node structure for a singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to append a new node to the list
void append(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two large numbers represented by linked lists
struct Node* addLargeNumbers(struct Node* l1, struct Node* l2) {
    struct Node* result = NULL; // To store the result linked list
    struct Node* temp = NULL;
    int carry = 0;
    
    while (l1 != NULL || l2 != NULL || carry) {
        int sum = carry;
        
        if (l1 != NULL) {
            sum += l1->data;
            l1 = l1->next;
        }
        
        if (l2 != NULL) {
            sum += l2->data;
            l2 = l2->next;
        }
        
        // Calculate the carry and the digit to be stored
        carry = sum / 10;
        sum = sum % 10;
        
        // Create a new node for the sum and append it to the result
        append(&result, sum);
    }
    
    return result;
}

// Main function
int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;
    
    // Representing large numbers as linked lists
    // 1 -> 2 -> 3 -> 4 (Represents 1234)
    append(&num1, 4);
    append(&num1, 3);
    append(&num1, 2);
    append(&num1, 1);
    
    // 9 -> 8 -> 7 -> 6 (Represents 6789)
    append(&num2, 6);
    append(&num2, 7);
    append(&num2, 8);
    append(&num2, 9);
    
    printf("Number 1: ");
    printList(num1);
    
    printf("Number 2: ");
    printList(num2);
    
    struct Node* result = addLargeNumbers(num1, num2);
    
    printf("Sum: ");
    printList(result);
    
    return 0;
}