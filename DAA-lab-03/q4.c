//algorithm------------->
// LIS(A, n):

//     for i = 0 to n-1
//         dp[i] = 1

//     answer = 1

//     for i = 1 to n-1
//         for j = 0 to i-1
//             if A[j] < A[i]
//                 dp[i] = max(dp[i], dp[j] + 1)

//         answer = max(answer, dp[i])

//     return answer....................................................................................................
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
 * Returns the length of the Longest Increasing Subsequence.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
int longestIncreasingSubsequence(int A[], int n) {
    if (n == 0)
        return 0;

    int *dp = (int *)malloc(n * sizeof(int));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int answer = 1;

    // Every element by itself is an increasing subsequence of length 1.
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    // Calculate the longest increasing subsequence ending at each i.
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {

            if (A[j] < A[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
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

    if (n < 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    if (n == 0) {
        printf("Length of LIS: 0\n");
        return 0;
    }

    int *A = (int *)malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int result = longestIncreasingSubsequence(A, n);

    printf("Length of Longest Increasing Subsequence: %d\n", result);

    free(A);

    return 0;
}
// output
// Enter 6 integers:
// 54 12 13 57 111 121
// Length of Longest Increasing Subsequence: 5
