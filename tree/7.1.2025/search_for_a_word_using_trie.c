#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    bool is_end_of_word;  // True if the node represents the end of a word
    struct Node *children[26]; // 26 possible characters (a to z)
};

struct Node* createNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->is_end_of_word = false;
    
    // Initialize all children to NULL
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

// Insert a word into the Trie
void insert(struct Node *root, const char *word) {
    struct Node *current = root;
    while (*word) {
        int index = *word - 'a';  // Get index (0 to 25 for 'a' to 'z')

        // If the current character's node doesn't exist, create a new one
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }

        // Move to the next node in the Trie
        current = current->children[index];
        word++;
    }
    
    // Mark the end of the word
    current->is_end_of_word = true;
}

// Search for a word in the Trie
bool search(struct Node *root, const char *word) {
    struct Node *current = root;
    while (*word) {
        int index = *word - 'a';  // Get index (0 to 25 for 'a' to 'z')

        // If the current character's node doesn't exist, return false
        if (current->children[index] == NULL) {
            return false;
        }

        // Move to the next node in the Trie
        current = current->children[index];
        word++;
    }
    
    // Return true if we reached the end of the word and it's marked as the end of a word
    return current->is_end_of_word;
}

// Perform inorder traversal of the Trie (for debugging/printing)
void inorder(struct Node *root, char *buffer, int depth) {
    if (root == NULL) {
        return;
    }

    if (root->is_end_of_word) {
        buffer[depth] = '\0';  // Null-terminate the string
        printf("%s ", buffer); // Print the current word
    }

    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = i + 'a';  // Assign character 'a' to 'z'
            inorder(root->children[i], buffer, depth + 1);
        }
    }
}

int main() {
    struct Node *root = createNode();
    char word[100];
    int option;

    while (1) {
        printf("Enter an option (1: Insert, 2: Search, 3: Display, 0: Exit): ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter a word to insert: ");
                scanf("%s", word);
                insert(root, word);
                printf("Word inserted.\n");
                break;

            case 2:
                printf("Enter a word to search: ");
                scanf("%s", word);
                if (search(root, word)) {
                    printf("Word found in Trie.\n");
                } else {
                    printf("Word not found in Trie.\n");
                }
                break;

            case 3:
                printf("Words in the Trie (in-order): ");
                char buffer[100];
                inorder(root, buffer, 0);
                printf("\n");
                break;

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}
