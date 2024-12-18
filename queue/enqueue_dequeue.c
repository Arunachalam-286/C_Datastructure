#include <stdio.h>
#include <string.h>

#define MAX 100 // Maximum size for operations

// Function to check if the sequence of operations is valid
int isValidQueueSequence(const char* operations) {
    int size = 0; // To track the current size of the queue

    // Traverse the sequence of operations
    for (int i = 0; i < strlen(operations); i++) {
        if (operations[i] == 'E') { // Enqueue operation
            size++;
        } else if (operations[i] == 'D') { // Dequeue operation
            if (size == 0) { // Dequeue not possible if queue is empty
                return 0;
            }
            size--;
        } else {
            // Invalid character in the sequence
            return 0;
        }
    }
    return 1; // Sequence is valid if all conditions are satisfied
}

// Main function
int main() {
    char operations[MAX];

    printf("Enter the sequence of operations (E for Enqueue, D for Dequeue): ");
    scanf("%s", operations);

    if (isValidQueueSequence(operations)) {
        printf("The sequence of operations is valid for a queue.\n");
    } else {
        printf("The sequence of operations is not valid for a queue.\n");
    }

    return 0;
}
