#include <stdio.h>

int main()
{
    int n, i, j;
    int totalCoins, minimumMoves;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    totalCoins = n * (n + 1) / 2;
    minimumMoves = totalCoins / 3;

    /* Input pattern */
    printf("\nInput Pattern:\n\n");

    for (i = 1; i <= n; i++)
    {
        /* Spaces */
        for (j = 1; j <= n - i; j++)
            printf("  ");

        /* Coins */
        for (j = 1; j <= i; j++)
            printf("O   ");

        printf("\n");
    }

    /* Output pattern */
    printf("\nOutput Pattern (Inverted):\n\n");

    for (i = 1; i <=n; i++)
    {
        /* Spaces */
        for (j = 1; j < i; j++)
            printf("  ");
        for (j = 1; j <n-i+2; j++)
            printf("O   ");

        /* Coins */

        printf("\n");
    }

    printf("\nTotal number of coins = %d\n", totalCoins);
    printf("Minimum number of moves = %d\n", minimumMoves);

    return 0;
}