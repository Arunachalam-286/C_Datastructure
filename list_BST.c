#include <stdio.h>
#include <stdlib.h>

// Definition of a linked list node
struct ListNode {
    int data;
    struct ListNode* next;
};

// Definition of a binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new linked list node
struct ListNode* createListNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new tree node
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to count the number of nodes in the linked list
int countNodes(struct ListNode* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Function to build a BST from the linked list
struct TreeNode* sortedListToBSTHelper(struct ListNode** head, int n) {
    if (n <= 0) {
        return NULL;
    }

    // Construct the left subtree
    struct TreeNode* left = sortedListToBSTHelper(head, n / 2);

    // Create the root node using the current list node
    struct TreeNode* root = createTreeNode((*head)->data);

    // Move the list pointer to the next node
    *head = (*head)->next;

    // Construct the right subtree
    root->right = sortedListToBSTHelper(head, n - n / 2 - 1);

    root->left = left;
    return root;
}

// Function to convert a sorted linked list to a balanced BST
struct TreeNode* sortedListToBST(struct ListNode* head) {
    int n = countNodes(head);
    return sortedListToBSTHelper(&head, n);
}

// Function to print the BST in-order (for verification)
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Example usage
int main() {
    // Create a sorted linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
    struct ListNode* head = createListNode(1);
    head->next = createListNode(2);
    head->next->next = createListNode(3);
    head->next->next->next = createListNode(4);
    head->next->next->next->next = createListNode(5);
    head->next->next->next->next->next = createListNode(6);
    head->next->next->next->next->next->next = createListNode(7);

    // Convert the linked list to a balanced BST
    struct TreeNode* root = sortedListToBST(head);

    // Print the BST in-order
    printf("In-order traversal of the constructed BST: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}