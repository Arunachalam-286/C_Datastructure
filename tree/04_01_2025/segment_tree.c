#include<stdio.h>
#include<stdlib.h>

struct SegmentTreeNode {
    int sum; // Stores the sum for this segment
    int start, end; // Range of this segment
    struct SegmentTreeNode *left, *right;
};

struct SegmentTreeNode* createNode(int start, int end) {
    struct SegmentTreeNode *newNode = (struct SegmentTreeNode*)malloc(sizeof(struct SegmentTreeNode));
    newNode->start = start;
    newNode->end = end;
    newNode->sum = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct SegmentTreeNode* buildTree(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    struct SegmentTreeNode *node = createNode(start, end);

    if (start == end) {
        // Leaf node, store the array value
        node->sum = arr[start];
    } else {
        int mid = (start + end) / 2;
        node->left = buildTree(arr, start, mid);
        node->right = buildTree(arr, mid + 1, end);
        node->sum = (node->left ? node->left->sum : 0) + 
                    (node->right ? node->right->sum : 0);
    }
    return node;
}

int rangeSumQuery(struct SegmentTreeNode *node, int start, int end) {
    if (node == NULL || start > node->end || end < node->start)
        return 0;

    if (start <= node->start && end >= node->end)
        return node->sum;

    return rangeSumQuery(node->left, start, end) + 
           rangeSumQuery(node->right, start, end);
}

void update(struct SegmentTreeNode *node, int index, int value) {
    if (node == NULL || index < node->start || index > node->end)
        return;

    if (node->start == node->end) {
        node->sum = value;
        return;
    }

    update(node->left, index, value);
    update(node->right, index, value);

    node->sum = (node->left ? node->left->sum : 0) + 
                (node->right ? node->right->sum : 0);
}

void inorderTraversal(struct SegmentTreeNode *node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("[%d, %d]: %d\n", node->start, node->end, node->sum);
    inorderTraversal(node->right);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct SegmentTreeNode *root = buildTree(arr, 0, n - 1);

    printf("Inorder traversal of segment tree:\n");
    inorderTraversal(root);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Range Sum Query\n");
        printf("2. Update Value\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int start, end;
            printf("Enter the range (start and end): ");
            scanf("%d %d", &start, &end);
            int sum = rangeSumQuery(root, start, end);
            printf("Range Sum [%d, %d]: %d\n", start, end, sum);
        } else if (choice == 2) {
            int index, value;
            printf("Enter the index and new value: ");
            scanf("%d %d", &index, &value);
            update(root, index, value);
            printf("Value updated.\n");
        }
    } while (choice != 3);

    return 0;
}
