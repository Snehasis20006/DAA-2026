#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    KEEP,
    INSERT,
    DELETE,
    SUBSTITUTE
} OperationType;

typedef struct {
    OperationType type;
    char from;
    char to;
} Operation;

/*
 * Returns the minimum of three integers.
 */
int minimum3(int a, int b, int c) {
    int result = a;

    if (b < result)
        result = b;

    if (c < result)
        result = c;

    return result;
}

/*
 * Computes the edit distance and stores the DP table.
 */
int editDistance(const char *A, const char *B, int m, int n, int **dp) {

    // Base cases
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    // Fill DP table
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (A[i - 1] == B[j - 1]) {

                // Characters already match.
                dp[i][j] = dp[i - 1][j - 1];

            } else {

                int deletion = dp[i - 1][j] + 1;
                int insertion = dp[i][j - 1] + 1;
                int substitution = dp[i - 1][j - 1] + 1;

                dp[i][j] = minimum3(
                    deletion,
                    insertion,
                    substitution
                );
            }
        }
    }

    return dp[m][n];
}

/*
 * Performs traceback and stores operations.
 *
 * The traceback starts from dp[m][n] and moves toward dp[0][0].
 * Operations are initially stored backwards.
 */
int traceback(
    const char *A,
    const char *B,
    int m,
    int n,
    int **dp,
    Operation *operations
) {
    int i = m;
    int j = n;
    int count = 0;

    while (i > 0 || j > 0) {

        /*
         * If both characters are equal, no operation is required.
         */
        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1] &&
            dp[i][j] == dp[i - 1][j - 1]) {

            operations[count].type = KEEP;
            operations[count].from = A[i - 1];
            operations[count].to = B[j - 1];

            count++;

            i--;
            j--;
        }

        /*
         * Substitution.
         */
        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1) {

            operations[count].type = SUBSTITUTE;
            operations[count].from = A[i - 1];
            operations[count].to = B[j - 1];

            count++;

            i--;
            j--;
        }

        /*
         * Deletion.
         */
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1) {

            operations[count].type = DELETE;
            operations[count].from = A[i - 1];
            operations[count].to = '-';

            count++;

            i--;
        }

        /*
         * Insertion.
         */
        else if (j > 0 &&
                 dp[i][j] == dp[i][j - 1] + 1) {

            operations[count].type = INSERT;
            operations[count].from = '-';
            operations[count].to = B[j - 1];

            count++;

            j--;
        }
    }

    return count;
}

/*
 * Prints traceback operations in forward order.
 */
void printOperations(Operation *operations, int count) {

    printf("\nTraceback operations:\n");
    printf("--------------------\n");

    int operationNumber = 1;

    /*
     * Operations were generated from the end to the beginning,
     * so print them in reverse order.
     */
    for (int i = count - 1; i >= 0; i--) {

        switch (operations[i].type) {

            case KEEP:
                printf(
                    "%d. Keep '%c'\n",
                    operationNumber,
                    operations[i].from
                );
                break;

            case INSERT:
                printf(
                    "%d. Insert '%c'\n",
                    operationNumber,
                    operations[i].to
                );
                break;

            case DELETE:
                printf(
                    "%d. Delete '%c'\n",
                    operationNumber,
                    operations[i].from
                );
                break;

            case SUBSTITUTE:
                printf(
                    "%d. Substitute '%c' with '%c'\n",
                    operationNumber,
                    operations[i].from,
                    operations[i].to
                );
                break;
        }

        operationNumber++;
    }
}

int main() {

    char A[1000];
    char B[1000];

    printf("Enter string A: ");
    scanf("%999s", A);

    printf("Enter string B: ");
    scanf("%999s", B);

    int m = strlen(A);
    int n = strlen(B);

    /*
     * Dynamically allocate the DP table.
     */
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= m; i++) {

        dp[i] = (int *)malloc((n + 1) * sizeof(int));

        if (dp[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int k = 0; k < i; k++) {
                free(dp[k]);
            }

            free(dp);
            return 1;
        }
    }

    /*
     * Calculate edit distance.
     */
    int distance = editDistance(A, B, m, n, dp);

    printf("\nEdit Distance: %d\n", distance);

    /*
     * At most m+n operations are required.
     */
    Operation *operations =
        (Operation *)malloc((m + n + 1) * sizeof(Operation));

    if (operations == NULL) {
        printf("Memory allocation failed.\n");

        for (int i = 0; i <= m; i++) {
            free(dp[i]);
        }

        free(dp);
        return 1;
    }

    /*
     * Perform traceback.
     */
    int operationCount =
        traceback(A, B, m, n, dp, operations);

    /*
     * Print traceback.
     */
    printOperations(operations, operationCount);

    /*
     * Free memory.
     */
    free(operations);

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }

    free(dp);

    return 0;
}
// output
// Enter string A: snehasis
// Enter string B: snehamallik

// Edit Distance: 5

// Traceback operations:
// --------------------
// 1. Keep 's'
// 2. Keep 'n'
// 3. Keep 'e'
// 4. Keep 'h'
// 5. Insert 'a'
// 6. Insert 'm'
// 7. Keep 'a'
// 8. Insert 'l'
// 9. Substitute 's' with 'l'
// 10. Keep 'i'
// 11. Substitute 's' with 'k'