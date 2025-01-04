#include<stdio.h>
#include<stdlib.h>

// Structure for Node of n-ary tree
struct Node {
    int data;
    struct Node **children;  // Pointer to array of children
    int childCount;          // Number of children
};

// Create a new node for the n-ary tree
struct Node* createNode(int val, int childCount) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->childCount = childCount;
    newNode->children = (struct Node**)malloc(childCount * sizeof(struct Node*)); // Allocate memory for children
    return newNode;
}

// Function to insert a child node at a particular index
void insertChild(struct Node *parent, struct Node *child, int index) {
    if (index < parent->childCount) {
        parent->children[index] = child;
    }
}

// Function to find the height of the tree rooted at the given node
int findHeight(struct Node *node, int *diameter) {
    if (node == NULL) {
        return 0;
    }

    // Store the heights of the subtrees
    int heights[node->childCount];
    int max1 = 0, max2 = 0;

    // Find heights of all children
    for (int i = 0; i < node->childCount; i++) {
        heights[i] = findHeight(node->children[i], diameter);
        // Find the two largest heights
        if (heights[i] > max1) {
            max2 = max1;
            max1 = heights[i];
        } else if (heights[i] > max2) {
            max2 = heights[i];
        }
    }

    // Calculate the diameter at this node (max1 + max2 gives the longest path through this node)
    *diameter = *diameter > (max1 + max2) ? *diameter : (max1 + max2);

    return 1 + max1; // Return the height of the current node
}

// Function to calculate the diameter of the tree
int findDiameter(struct Node *root) {
    int diameter = 0;
    findHeight(root, &diameter);
    return diameter;
}

int main() {
    int val, childCount;

    // Read the root node value
    printf("Enter root node value: ");
    scanf("%d", &val);
    printf("Enter number of children for the root node: ");
    scanf("%d", &childCount);

    // Create the root node
    struct Node *root = createNode(val, childCount);

    // Insert child nodes for the root node
    for (int i = 0; i < childCount; i++) {
        printf("Enter value for child %d: ", i + 1);
        scanf("%d", &val);
        printf("Enter number of children for this child node: ");
        scanf("%d", &childCount);

        struct Node *child = createNode(val, childCount);
        insertChild(root, child, i);
    }

    // Calculate and print the diameter of the n-ary tree
    int diameter = findDiameter(root);
    printf("Diameter of the tree is: %d\n", diameter);

    return 0;
}
