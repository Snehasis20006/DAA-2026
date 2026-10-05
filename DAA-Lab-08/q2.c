#include <stdio.h>

int main()
{
    int n, V;
    int coins[100];
    long long dp[1000];

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

    /* Initialize dp array */
    for (i = 0; i <= V; i++)
    {
        dp[i] = 0;
    }

    /* There is one way to make amount 0 */
    dp[0] = 1;

    /* Process each coin */
    for (i = 0; i < n; i++)
    {
        for (j = coins[i]; j <= V; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    printf("Total number of ways = %lld\n", dp[V]);

    return 0;
}