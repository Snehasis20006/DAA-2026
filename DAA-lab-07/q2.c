#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    int E, F;
    int e, f, x;
    int broken, notBroken, worst;
    int **dp;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    dp = (int **)malloc((E + 1) * sizeof(int *));

    for (e = 0; e <= E; e++)
    {
        dp[e] = (int *)malloc((F + 1) * sizeof(int));
    }

    for (e = 1; e <= E; e++)
    {
        dp[e][0] = 0;

        if (F >= 1)
            dp[e][1] = 1;
    }

    for (f = 0; f <= F; f++)
    {
        dp[1][f] = f;
    }

    for (e = 2; e <= E; e++)
    {
        for (f = 2; f <= F; f++)
        {
            dp[e][f] = 999999;

            for (x = 1; x <= f; x++)
            {
                broken = dp[e - 1][x - 1];
                notBroken = dp[e][f - x];

                worst = max(broken, notBroken);

                if (worst + 1 < dp[e][f])
                    dp[e][f] = worst + 1;
            }
        }
    }

    printf("\nMinimum number of drops = %d\n", dp[E][F]);

    for (e = 0; e <= E; e++)
        free(dp[e]);

    free(dp);

    return 0;
}