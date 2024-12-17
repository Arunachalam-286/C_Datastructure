#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define URL_LENGTH 100

// Stack structure to store URLs
typedef struct {
    char data[MAX_SIZE][URL_LENGTH];
    int top;
} Stack;

// Initialize a stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Push a URL onto the stack
void push(Stack* s, const char* url) {
    if (s->top < MAX_SIZE - 1) {
        strcpy(s->data[++(s->top)], url);
    }
}

// Pop a URL from the stack
char* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return NULL;
}

// Peek the top of the stack
char* peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    }
    return NULL;
}

// Simulate the browser navigation
int main() {
    Stack backStack, forwardStack;
    initStack(&backStack);
    initStack(&forwardStack);

    char currentPage[URL_LENGTH] = "home";  // Starting page
    int choice;
    char newURL[URL_LENGTH];

    while (1) {
        printf("\n--- Browser Navigation ---\n");
        printf("Current Page: %s\n", currentPage);
        printf("1. Visit new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Visit a new page
                printf("Enter URL: ");
                scanf("%s", newURL);

                // Push the current page to the back stack
                push(&backStack, currentPage);

                // Clear the forward stack as forward history is invalidated
                initStack(&forwardStack);

                // Update the current page
                strcpy(currentPage, newURL);
                break;

            case 2: // Go back
                if (!isEmpty(&backStack)) {
                    // Push the current page onto the forward stack
                    push(&forwardStack, currentPage);

                    // Pop the top of the back stack as the new current page
                    strcpy(currentPage, pop(&backStack));
                } else {
                    printf("No pages in back history.\n");
                }
                break;

            case 3: // Go forward
                if (!isEmpty(&forwardStack)) {
                    // Push the current page onto the back stack
                    push(&backStack, currentPage);

                    // Pop the top of the forward stack as the new current page
                    strcpy(currentPage, pop(&forwardStack));
                } else {
                    printf("No pages in forward history.\n");
                }
                break;

            case 4: // Exit
                printf("Exiting browser navigation.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
