#include <stdio.h>

// Function to calculate the time needed to buy tickets
int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    int time = 0;

    while (1) {
        for (int i = 0; i < ticketsSize; i++) {
            if (tickets[i] > 0) {
                // Person at position `i` buys one ticket
                tickets[i]--;
                time++;

                // If the person at position `k` has finished buying tickets, return the time
                if (i == k && tickets[i] == 0) {
                    return time;
                }
            }
        }
    }
}

// Main function to test the solution
int main() {
    int tickets[] = {2, 3, 2};
    int ticketsSize = sizeof(tickets) / sizeof(tickets[0]);
    int k = 2; // Position of the person in the queue

    int result = timeRequiredToBuy(tickets, ticketsSize, k);
    printf("Time needed to buy tickets: %d\n", result);

    return 0;
}
