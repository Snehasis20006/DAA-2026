/*
Q1: Fractional Knapsack with Deterioration Rate
IMPORTANT: The assignment does not define how consumption duration maps to time.
This program uses a simple discrete-slot interpretation: at each integer time t,
choose the remaining item with the highest positive density (value/weight - decay*t),
take as much as possible, then advance t by one. Confirm this assumption with your instructor.
*/
#include <stdio.h>

#define MAXN 100

int main(void) {
    int n, i, t = 0;
    double capacity, total = 0.0;
    double value[MAXN], weight[MAXN], decay[MAXN], remaining[MAXN];

    printf("Enter number of items (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("Invalid number of items.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate for item %d: ", i + 1);
        if (scanf("%lf %lf %lf", &value[i], &weight[i], &decay[i]) != 3 ||
            value[i] < 0 || weight[i] <= 0 || decay[i] < 0) {
            printf("Invalid item data.\n");
            return 1;
        }
        remaining[i] = weight[i];
    }
    printf("Enter knapsack capacity: ");
    if (scanf("%lf", &capacity) != 1 || capacity < 0) {
        printf("Invalid capacity.\n");
        return 1;
    }

    printf("\nChosen order (discrete-slot model):\n");
    while (capacity > 1e-9) {
        int best = -1;
        double bestDensity = 0.0;
        for (i = 0; i < n; i++) {
            double density;
            if (remaining[i] <= 1e-9) continue;
            density = value[i] / weight[i] - decay[i] * t;
            if (density > bestDensity) {
                bestDensity = density;
                best = i;
            }
        }
        if (best == -1) break;

        {
            double take = remaining[best];
            double gain;
            if (take > capacity) take = capacity;
            gain = take * bestDensity;
            printf("Time %d: take %.2f weight of item %d (effective density %.2f)\n",
                   t, take, best + 1, bestDensity);
            total += gain;
            remaining[best] -= take;
            capacity -= take;
        }
        t++;
    }
    printf("Total value under this model: %.2f\n", total);
    printf("Time complexity: O(n^2) in the worst case; space complexity: O(n).\n");
    return 0;
}
