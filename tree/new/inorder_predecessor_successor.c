#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

void insert(struct Node **node, int val) {
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
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

struct Node* findPredecessor(struct Node* node) {
    if (node == NULL || node->left == NULL) return NULL;
    struct Node* temp = node->left;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

struct Node* findSuccessor(struct Node* node) {
    if (node == NULL || node->right == NULL) return NULL;
    struct Node* temp = node->right;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

void findPredecessorSuccessor(struct Node* root, int key, struct Node** pred, struct Node** succ) {
    if (root == NULL) return;

    if (root->data == key) {
        // Find predecessor
        *pred = findPredecessor(root);

        // Find successor
        *succ = findSuccessor(root);
    } else if (key < root->data) {
        *succ = root; // Current node is a potential successor
        findPredecessorSuccessor(root->left, key, pred, succ);
    } else {
        *pred = root; // Current node is a potential predecessor
        findPredecessorSuccessor(root->right, key, pred, succ);
    }
}

int main() {
    int val;
    printf("Enter values to insert into the BST (-1 to stop):\n");
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Enter a key to find its predecessor and successor: ");
    int key;
    scanf("%d", &key);

    struct Node *pred = NULL, *succ = NULL;
    findPredecessorSuccessor(root, key, &pred, &succ);

    if (pred != NULL)
        printf("Predecessor: %d\n", pred->data);
    else
        printf("Predecessor: None\n");

    if (succ != NULL)
        printf("Successor: %d\n", succ->data);
    else
        printf("Successor: None\n");

    return 0;
}
