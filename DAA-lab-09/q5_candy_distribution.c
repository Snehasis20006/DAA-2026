/* Q5: Minimum candies using left-to-right and right-to-left passes. */
#include <stdio.h>
#define MAXN 100000

int main(void) {
    int n, i, ratings[MAXN];
    long long candies[MAXN], total = 0;
    printf("Enter number of children (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid input.\n"); return 1; }
    for (i = 0; i < n; i++) {
        printf("Enter rating of child %d: ", i + 1);
        if (scanf("%d", &ratings[i]) != 1) { printf("Invalid rating.\n"); return 1; }
        candies[i] = 1;
    }
    for (i = 1; i < n; i++)
        if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
    for (i = n - 2; i >= 0; i--)
        if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1])
            candies[i] = candies[i + 1] + 1;
    for (i = 0; i < n; i++) total += candies[i];
    printf("Candies assigned: ");
    for (i = 0; i < n; i++) printf("%lld ", candies[i]);
    printf("\nMinimum total candies: %lld\n", total);
    printf("Time complexity: O(n); space complexity: O(n).\n");
    return 0;
}
