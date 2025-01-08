#include<stdio.h>
#include<stdlib.h>

// Function to calculate the nth Catalan number
int countUniqueBSTs(int n) {
    int *catalan = (int*)malloc((n + 1) * sizeof(int));

    // Base cases
    catalan[0] = 1; // Empty tree
    catalan[1] = 1; // Single node tree

    // Fill the catalan array for numbers 2 to n
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }

    int result = catalan[n];
    free(catalan);
    return result;
}

// Binary Search Tree structure and basic operations
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *root = NULL;

void insert(struct Node **node, int val) {
    // If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }

    // Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

int main() {
    int n;

    printf("Enter the number of distinct keys (n): ");
    scanf("%d", &n);

    int uniqueBSTs = countUniqueBSTs(n);

    printf("Number of unique BSTs that can be formed with %d keys: %d\n", n, uniqueBSTs);

    // Optional: Construct a sample BST by inserting elements
    printf("Enter keys to construct a sample BST (-1 to stop): ");
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    // Display the inorder traversal of the constructed BST
    printf("Inorder Traversal of the constructed BST: ");
    inorder(root);
    printf("\n");

    return 0;
}
