#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26  // Assuming only lowercase English letters

// Definition of a Trie Node
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int wordCount;  // Tracks the number of words passing through this node
};

// Function to create a new Trie Node
struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;
    node->wordCount = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}

// Function to insert a word into the Trie
void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    while (*word) {
        int index = *word - 'a';

        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }

        current = current->children[index];
        current->wordCount++;  // Increment the word count for the node
        word++;
    }

    current->isEndOfWord = true;  // Mark the end of the word
}

// Function to find the node corresponding to the last character of the prefix
struct TrieNode* findPrefixNode(struct TrieNode* root, const char* prefix) {
    struct TrieNode* current = root;

    while (*prefix) {
        int index = *prefix - 'a';

        if (current->children[index] == NULL) {
            return NULL;  // Prefix not found
        }

        current = current->children[index];
        prefix++;
    }

    return current;  // Return the node corresponding to the last character of the prefix
}

// Function to count the number of words starting with a given prefix
int countWordsStartingWith(struct TrieNode* root, const char* prefix) {
    struct TrieNode* prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == NULL) {
        return 0;  // Prefix not found
    }

    return prefixNode->wordCount;  // Return the word count stored in the prefix node
}

// Main function to test the implementation
int main() {
    // Create the root of the Trie
    struct TrieNode* root = createNode();

    // Insert words into the Trie
    insert(root, "apple");
    insert(root, "app");
    insert(root, "apex");
    insert(root, "banana");
    insert(root, "bat");

    // Count words starting with given prefixes
    printf("Words starting with 'app': %d\n", countWordsStartingWith(root, "app"));
    printf("Words starting with 'ap': %d\n", countWordsStartingWith(root, "ap"));
    printf("Words starting with 'ba': %d\n", countWordsStartingWith(root, "ba"));
    printf("Words starting with 'cat': %d\n", countWordsStartingWith(root, "cat"));

    return 0;
}
