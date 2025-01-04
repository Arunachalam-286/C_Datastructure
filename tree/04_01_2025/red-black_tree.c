#include<stdio.h>
#include<stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    enum Color color;
} *root = NULL, *TNULL;

void initializeTNULL() {
    TNULL = (struct Node*)malloc(sizeof(struct Node));
    TNULL->color = BLACK;
    TNULL->left = NULL;
    TNULL->right = NULL;
    TNULL->parent = NULL;
}

void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void fixInsert(struct Node *k) {
    struct Node *u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}

void insert(int key) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->parent = NULL;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    struct Node *y = NULL;
    struct Node *x = root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == NULL) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == NULL) {
        return;
    }

    fixInsert(node);
}

void inorder(struct Node *node) {
    if (node != TNULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

int main() {
    initializeTNULL();

    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
