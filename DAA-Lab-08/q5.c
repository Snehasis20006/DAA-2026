#include <stdio.h>
#include <stdlib.h>

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

/*
 * Returns the maximum sum of a strictly increasing subsequence.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
long long maximumSumIncreasingSubsequence(int A[], int n) {
    if (n == 0)
        return 0;

    long long *dp = (long long *)malloc(n * sizeof(long long));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initially, each element forms a subsequence by itself.
    for (int i = 0; i < n; i++) {
        dp[i] = A[i];
    }

    long long answer = dp[0];

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {
                dp[i] = max(dp[i], dp[j] + A[i]);
            }
        }

        answer = max(answer, dp[i]);
    }

    free(dp);

    return answer;
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d positive integers:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);

        if (A[i] <= 0) {
            printf("All elements must be positive.\n");
            free(A);
            return 1;
        }
    }

    long long result = maximumSumIncreasingSubsequence(A, n);

    printf("Maximum Sum of Increasing Subsequence: %lld\n", result);

    free(A);

    return 0;
}
// output
// Enter 6 positive integers:
// 23 12 34 11 14 15
// Maximum Sum of Increasing Subsequence: 57