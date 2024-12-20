#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
struct ListNode {
    int val;
    struct ListNode *next;
};

// Define a structure for the priority queue (min-heap)
struct MinHeapNode {
    int value;
    struct ListNode* node; // Pointer to the linked list node
    int listIndex;         // Index of the list from which the node is taken
};

// Min-heap comparator function
int compare(struct MinHeapNode a, struct MinHeapNode b) {
    return a.value - b.value;
}

// Min-heapify the heap
void minHeapify(struct MinHeapNode heap[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && compare(heap[left], heap[smallest]) < 0) {
        smallest = left;
    }
    if (right < size && compare(heap[right], heap[smallest]) < 0) {
        smallest = right;
    }

    if (smallest != index) {
        struct MinHeapNode temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;

        minHeapify(heap, size, smallest);
    }
}

// Function to extract the minimum value from the heap
struct MinHeapNode extractMin(struct MinHeapNode heap[], int* size) {
    struct MinHeapNode minNode = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    minHeapify(heap, *size, 0);
    return minNode;
}

// Function to insert a new node into the heap
void insertHeap(struct MinHeapNode heap[], int* size, struct MinHeapNode node) {
    heap[*size] = node;
    (*size)++;
    int i = *size - 1;

    // Heapify up
    while (i > 0 && compare(heap[(i - 1) / 2], heap[i]) > 0) {
        struct MinHeapNode temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Function to merge k sorted linked lists using a priority queue
struct ListNode* mergeKSortedLists(struct ListNode* lists[], int k) {
    struct MinHeapNode heap[k];
    int heapSize = 0;

    // Build the initial heap with the first node from each list
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL) {
            struct MinHeapNode node;
            node.value = lists[i]->val;
            node.node = lists[i];
            node.listIndex = i;
            insertHeap(heap, &heapSize, node);
            lists[i] = lists[i]->next; // Move to the next node in the list
        }
    }

    struct ListNode* result = NULL;
    struct ListNode* tail = NULL;

    // Extract the minimum element from the heap and insert the next node from the same list
    while (heapSize > 0) {
        struct MinHeapNode minNode = extractMin(heap, &heapSize);

        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = minNode.value;
        newNode->next = NULL;

        if (result == NULL) {
            result = newNode;
            tail = result;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        // If there is a next node in the same list, add it to the heap
        if (lists[minNode.listIndex] != NULL) {
            struct MinHeapNode nextNode;
            nextNode.value = lists[minNode.listIndex]->val;
            nextNode.node = lists[minNode.listIndex];
            nextNode.listIndex = minNode.listIndex;
            insertHeap(heap, &heapSize, nextNode);
            lists[minNode.listIndex] = lists[minNode.listIndex]->next;
        }
    }

    return result;
}

// Helper function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Helper function to create a new linked list node
struct ListNode* newNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

int main() {
    // Example lists
    struct ListNode* list1 = newNode(1);
    list1->next = newNode(4);
    list1->next->next = newNode(5);

    struct ListNode* list2 = newNode(1);
    list2->next = newNode(3);
    list2->next->next = newNode(4);

    struct ListNode* list3 = newNode(2);
    list3->next = newNode(6);

    // Array of lists
    struct ListNode* lists[] = { list1, list2, list3 };

    // Merge the k sorted lists
    struct ListNode* mergedList = mergeKSortedLists(lists, 3);

    // Print the merged list
    printf("Merged List: ");
    printList(mergedList);

    return 0;
}
