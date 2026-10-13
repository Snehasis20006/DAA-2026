/*
Q9: Exact optimal alphabetic tree using dynamic programming.
NOTE: This solves the stated minimum weighted-depth objective while preserving
the left-to-right order. It is NOT a Hu-Tucker greedy implementation; Hu-Tucker
is more involved. Ask your instructor whether this exact DP alternative is accepted.
*/
#include <stdio.h>
#define MAXN 100

long long w[MAXN], prefix[MAXN + 1], dp[MAXN][MAXN];
int split[MAXN][MAXN];

void printTree(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }
    printf("(");
    printTree(i, split[i][j]);
    printf(" ");
    printTree(split[i][j] + 1, j);
    printf(")");
}

int main(void) {
    int n, i, j, len, k;
    printf("Enter number of ordered weights (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid input.\n"); return 1; }
    prefix[0] = 0;
    for (i = 0; i < n; i++) {
        printf("Enter weight %d: ", i + 1);
        if (scanf("%lld", &w[i]) != 1 || w[i] < 0) { printf("Invalid weight.\n"); return 1; }
        prefix[i + 1] = prefix[i] + w[i];
        dp[i][i] = 0;
    }
    for (len = 2; len <= n; len++) {
        for (i = 0; i + len <= n; i++) {
            j = i + len - 1;
            dp[i][j] = -1;
            for (k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k + 1][j] + (prefix[j + 1] - prefix[i]);
                if (dp[i][j] == -1 || cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    printf("Minimum weighted external path length: %lld\n", dp[0][n - 1]);
    printf("Alphabetic tree structure (leaf labels are input positions): ");
    printTree(0, n - 1);
    printf("\nTime complexity: O(n^3); space complexity: O(n^2).\n");
    return 0;
}
