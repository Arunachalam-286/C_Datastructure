#include <stdio.h>

// Function to calculate the number of unique BSTs
unsigned long long numTrees(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long long catalan[n + 1];
    catalan[0] = 1;
    catalan[1] = 1;

    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - 1 - j];
        }
    }

    return catalan[n];
}

int main() {
    int n;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    unsigned long long result = numTrees(n);
    printf("The number of unique BSTs with %d nodes is: %llu\n", n, result);

    return 0;
}
