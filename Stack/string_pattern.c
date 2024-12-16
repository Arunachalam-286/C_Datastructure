#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

// Stack structure for integers
typedef struct {
    int data[MAX_SIZE];
    int top;
} IntStack;

// Stack structure for strings
typedef struct {
    char* data[MAX_SIZE];
    int top;
} StringStack;

// Stack operations for integers
void pushInt(IntStack* stack, int value) {
    stack->data[++stack->top] = value;
}

int popInt(IntStack* stack) {
    return stack->data[stack->top--];
}

int isEmptyInt(IntStack* stack) {
    return stack->top == -1;
}

// Stack operations for strings
void pushString(StringStack* stack, char* value) {
    stack->data[++stack->top] = strdup(value);
}

char* popString(StringStack* stack) {
    char* topValue = stack->data[stack->top];
    stack->data[stack->top--] = NULL; // Avoid dangling pointer
    return topValue;
}

int isEmptyString(StringStack* stack) {
    return stack->top == -1;
}

// Function to decode the string
char* decodeString(const char* s) {
    IntStack repeatStack = {.top = -1};
    StringStack stringStack = {.top = -1};

    char currentString[MAX_SIZE] = "";
    int n = strlen(s);

    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) {
            // Read the full number
            int num = 0;
            while (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--; // Adjust index after overshooting
            pushInt(&repeatStack, num);
        } else if (s[i] == '[') {
            // Push current string to stack and reset it
            pushString(&stringStack, currentString);
            currentString[0] = '\0';
        } else if (s[i] == ']') {
            // Decode the current pattern
            int repeatCount = popInt(&repeatStack);
            char* previousString = popString(&stringStack);

            // Repeat the current string
            char repeatedString[MAX_SIZE] = "";
            for (int j = 0; j < repeatCount; j++) {
                strcat(repeatedString, currentString);
            }

            // Combine with the previous string
            strcpy(currentString, previousString);
            strcat(currentString, repeatedString);
            free(previousString);
        } else {
            // Add character to the current string
            int len = strlen(currentString);
            currentString[len] = s[i];
            currentString[len + 1] = '\0';
        }
    }

    // Final decoded string
    return strdup(currentString);
}

// Main function to test the solution
int main() {
    char input[MAX_SIZE];

    printf("Enter the encoded string: ");
    fgets(input, MAX_SIZE, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    char* result = decodeString(input);
    printf("Decoded string: %s\n", result);

    free(result);
    return 0;
}
