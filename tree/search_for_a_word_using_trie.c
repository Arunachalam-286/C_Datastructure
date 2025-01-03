#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of a Trie Node
#define ALPHABET_SIZE 26  // Assuming only lowercase English letters

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;  // True if the node represents the end of a word
};

// Function to create a new Trie Node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Function to insert a word into the Trie
void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    while (*word) {
        int index = *word - 'a';  // Calculate the index (0-25)

        if (current->children[index] == NULL) {
            current->children[index] = createNode();  // Create a new node if necessary
        }

        current = current->children[index];
        word++;
    }

    current->isEndOfWord = true;  // Mark the end of the word
}

// Function to search for a word in the Trie
bool search(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    while (*word) {
        int index = *word - 'a';

        if (current->children[index] == NULL) {
            return false;  // Word not found
        }

        current = current->children[index];
        word++;
    }

    return current->isEndOfWord;  // Return true if it's the end of a word
}

// Main function to test the search functionality
int main() {
    // Create the root of the Trie
    struct TrieNode* root = createNode();

    // Insert words into the Trie
    insert(root, "apple");
    insert(root, "app");
    insert(root, "banana");
    insert(root, "bat");

    // Search for words
    printf("Search 'apple': %s\n", search(root, "apple") ? "Found" : "Not Found");
    printf("Search 'app': %s\n", search(root, "app") ? "Found" : "Not Found");
    printf("Search 'batman': %s\n", search(root, "batman") ? "Found" : "Not Found");

    return 0;
}
