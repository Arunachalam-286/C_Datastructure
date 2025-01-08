#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node Structure
struct Node {
    struct Node *children[ALPHABET_SIZE]; // Child pointers for 26 lowercase English letters
    int isEndOfWord; // Flag to mark the end of a word
};

// Function to create a new Trie node
struct Node* createNode() {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to insert a string into the trie
void insert(struct Node *root, const char *word) {
    struct Node *current = root;
    int index;

    for (int i = 0; word[i] != '\0'; i++) {
        index = word[i] - 'a'; // Convert character to index (0-25)
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1; // Mark the end of the word
}

// Function to search for a string in the trie
int search(struct Node *root, const char *word) {
    struct Node *current = root;
    int index;

    for (int i = 0; word[i] != '\0'; i++) {
        index = word[i] - 'a'; // Convert character to index (0-25)
        if (current->children[index] == NULL) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->isEndOfWord; // Return 1 if it's the end of a word, 0 otherwise
}

// Function to check if there are any words with the given prefix
int startsWith(struct Node *root, const char *prefix) {
    struct Node *current = root;
    int index;

    for (int i = 0; prefix[i] != '\0'; i++) {
        index = prefix[i] - 'a'; // Convert character to index (0-25)
        if (current->children[index] == NULL) {
            return 0; // No word with the given prefix
        }
        current = current->children[index];
    }
    return 1; // Prefix exists
}

// Function to perform inorder traversal of the trie and print words
void inorderTraversal(struct Node *node, char *str, int level) {
    if (node == NULL) return;

    // If it's the end of a word, print the current word
    if (node->isEndOfWord) {
        str[level] = '\0';
        printf("%s\n", str);
    }

    // Traverse through all the children (26 characters)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            str[level] = 'a' + i; // Convert index to character
            inorderTraversal(node->children[i], str, level + 1);
        }
    }
}

int main() {
    struct Node *root = createNode();
    char word[100];
    
    printf("Enter words to insert into the Trie (Enter 'stop' to end):\n");
    while (1) {
        scanf("%s", word);
        if (strcmp(word, "stop") == 0) break; // Stop input if the word is "stop"
        insert(root, word);
    }
    
    printf("Inorder Traversal (words in the Trie):\n");
    char str[100];
    inorderTraversal(root, str, 0);

    printf("Enter a word to search: ");
    scanf("%s", word);
    if (search(root, word)) {
        printf("Word '%s' found in the Trie.\n", word);
    } else {
        printf("Word '%s' not found in the Trie.\n", word);
    }

    printf("Enter a prefix to search: ");
    scanf("%s", word);
    if (startsWith(root, word)) {
        printf("There are words with the prefix '%s'.\n", word);
    } else {
        printf("No words found with the prefix '%s'.\n", word);
    }

    return 0;
}
