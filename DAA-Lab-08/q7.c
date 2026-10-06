// R[0] = 0.........................................ALGORITHM ROD-CUTTING(P, n)................................................................

// for i = 1 to n:
//     R[i] = -∞
//     for j = 1 to i:
//         if P[j] + R[i-j] > R[i]:
//             R[i] = P[j] + R[i-j]
//             S[i] = j

// reconstruct:
//     length = n
//     while length > 0:
//         output S[length]
//         length = length - S[length]...............................................................................................



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void rodCutting(int price[], int n) {
    int *R = (int *)malloc((n + 1) * sizeof(int));
    int *S = (int *)malloc((n + 1) * sizeof(int));

    R[0] = 0;
    S[0] = 0;

    for (int i = 1; i <= n; i++) {
        R[i] = INT_MIN;

        for (int j = 1; j <= i; j++) {
            if (price[j] + R[i - j] > R[i]) {
                R[i] = price[j] + R[i - j];
                S[i] = j;
            }
        }
    }

    printf("Maximum revenue = %d\n", R[n]);

    printf("Optimal pieces: ");

    int length = n;

    while (length > 0) {
        printf("%d ", S[length]);
        length -= S[length];
    }

    printf("\n");

    free(R);
    free(S);
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter prices P[1] to P[%d]:\n", n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }

    rodCutting(price, n);

    free(price);

    return 0;
}
// output.................................................................................................................................
// Enter prices P[1] to P[7]:
// 1 3 4 5 6 7 8  
// Maximum revenue = 10
// Optimal pieces: 1 2 2 2 