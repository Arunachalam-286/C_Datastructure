#include <stdio.h>

// Function to find the starting gas station index
int canCompleteCircuit(int* gas, int* cost, int n) {
    int totalGas = 0, totalCost = 0, tank = 0, start = 0;

    for (int i = 0; i < n; i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        tank += gas[i] - cost[i];

        // If tank is negative, reset the starting station
        if (tank < 0) {
            start = i + 1;
            tank = 0;
        }
    }

    return (totalGas >= totalCost) ? start : -1;
}

// Main function to test the solution
int main() {
    int gas[] = {1, 2, 3, 4, 5};
    int cost[] = {3, 4, 5, 1, 2};
    int n = sizeof(gas) / sizeof(gas[0]);

    int result = canCompleteCircuit(gas, cost, n);

    if (result != -1) {
        printf("Start at gas station: %d\n", result);
    } else {
        printf("It is not possible to complete the circuit.\n");
    }

    return 0;
}
