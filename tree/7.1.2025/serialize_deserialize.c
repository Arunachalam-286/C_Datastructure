#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}*root = NULL;

void insert(struct Node **node, int val) {
    //1. If the current node is NULL, create a new node
    if (*node == NULL) {
        struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        *node = newnode;
        return;
    }
    //2. Insert into the left or right subtree based on value
    if (val < (*node)->data) {
        insert(&((*node)->left), val);
    } else {
        insert(&((*node)->right), val);
    }
}

// In-order Traversal
void inorder(struct Node *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

// Function to serialize the tree (pre-order traversal)
void serialize(struct Node *root, FILE *f) {
    if (root == NULL) {
        fprintf(f, "# ");  // Representing NULL with "#"
        return;
    }
    fprintf(f, "%d ", root->data);  // Store the node data
    serialize(root->left, f);  // Serialize left subtree
    serialize(root->right, f); // Serialize right subtree
}

// Function to deserialize the tree from a file
struct Node* deserialize(FILE *f) {
    char buffer[10];
    if (!fscanf(f, "%s", buffer)) {
        return NULL;
    }

    if (strcmp(buffer, "#") == 0) {
        return NULL;  // If it's a "#", this means it's a NULL child
    }

    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = atoi(buffer);  // Convert the string to an integer
    node->left = deserialize(f);  // Deserialize left subtree
    node->right = deserialize(f); // Deserialize right subtree
    return node;
}

int main() {
    int val;
    do {
        scanf("%d", &val);
        if (val != -1)
            insert(&root, val);
    } while (val != -1);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Serialize the tree to a file (could be a string or an array)
    FILE *f = fopen("tree.txt", "w");
    if (f == NULL) {
        printf("Failed to open file for serialization.\n");
        return 1;
    }
    serialize(root, f);
    fclose(f);

    // Deserialize the tree from the file
    f = fopen("tree.txt", "r");
    if (f == NULL) {
        printf("Failed to open file for deserialization.\n");
        return 1;
    }
    struct Node *deserializedTree = deserialize(f);
    fclose(f);

    // Print the inorder traversal of the deserialized tree
    printf("Inorder Traversal of the Deserialized Tree: ");
    inorder(deserializedTree);
    printf("\n");

    return 0;
}
