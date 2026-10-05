#include <stdio.h>

#define INF 999999

int main()
{
    int n, V;
    int coins[100];
    int dp[1000];

    int i, j;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    printf("Enter the coin denominations:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    /* Initialize DP array */
    dp[0] = 0;

    for (i = 1; i <= V; i++)
    {
        dp[i] = INF;
    }

    /* Calculate minimum coins */
    for (i = 1; i <= V; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INF)
            {
                if (dp[i - coins[j]] + 1 < dp[i])
                {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    /* Display result */
    if (dp[V] == INF)
    {
        printf("It is not possible to make the target amount.\n");
        printf("Minimum number of coins = -1\n");
    }
    else
    {
        printf("Minimum number of coins = %d\n", dp[V]);
    }

    return 0;
}
// ------sanmple potput-----
// Enter number of coin denominations: 7
// Enter the coin denominations:
// 1 2 3 4 5 6 7 
// Enter target amount: 7
// Minimum number of coins = 1