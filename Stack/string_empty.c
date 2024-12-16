#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1000

bool canBeReducedToEmptyString(const char *str) {
    char stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (top != -1 && stack[top] == str[i]) {
            // Pop the top element if it matches the current character
            top--;
        } else {
            // Push the current character onto the stack
            stack[++top] = str[i];
        }
    }

    // If the stack is empty, the string can be reduced to empty
    return top == -1;
}

int main() {
    char str[MAX_SIZE];
    printf("Enter a string: ");
    scanf("%s", str);

    if (canBeReducedToEmptyString(str)) {
        printf("The string can be reduced to an empty string.\n");
    } else {
        printf("The string cannot be reduced to an empty string.\n");
    }

    return 0;
}
