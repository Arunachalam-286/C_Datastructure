#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of a binary tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new tree node
struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Helper function to serialize the tree
void serializeHelper(struct TreeNode* root, char* result) {
    if (root == NULL) {
        strcat(result, "null,");
        return;
    }
    char buffer[16];
    sprintf(buffer, "%d,", root->val);
    strcat(result, buffer);
    serializeHelper(root->left, result);
    serializeHelper(root->right, result);
}

// Function to serialize the binary tree
char* serialize(struct TreeNode* root) {
    char* result = (char*)malloc(10000 * sizeof(char)); // Allocate sufficient memory
    result[0] = '\0'; // Initialize empty string
    serializeHelper(root, result);
    return result;
}

// Helper function to deserialize the tree
struct TreeNode* deserializeHelper(char** data) {
    if (strncmp(*data, "null", 4) == 0) {
        *data += 5; // Skip "null,"
        return NULL;
    }

    int val;
    sscanf(*data, "%d,", &val);
    *data = strchr(*data, ',') + 1; // Move pointer past the current value

    struct TreeNode* root = createTreeNode(val);
    root->left = deserializeHelper(data);
    root->right = deserializeHelper(data);
    return root;
}

// Function to deserialize the binary tree
struct TreeNode* deserialize(char* data) {
    return deserializeHelper(&data);
}

// Function to print the tree in preorder (for testing purposes)
void printPreOrder(struct TreeNode* root) {
    if (root == NULL) {
        printf("null ");
        return;
    }
    printf("%d ", root->val);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Main function to test serialization and deserialization
int main() {
    // Create a sample binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->right->left = createTreeNode(4);
    root->right->right = createTreeNode(5);

    // Serialize the tree
    char* serialized = serialize(root);
    printf("Serialized Tree: %s\n", serialized);

    // Deserialize the tree
    struct TreeNode* deserializedRoot = deserialize(serialized);
    printf("Deserialized Tree (Preorder): ");
    printPreOrder(deserializedRoot);
    printf("\n");

    // Free the allocated memory
    free(serialized);

    return 0;
}
