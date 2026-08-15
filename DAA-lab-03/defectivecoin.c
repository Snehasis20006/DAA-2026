#include <stdio.h>
#include <stdlib.h>

int findDefective(int coins[], int left, int right)
{
    int n = right - left + 1;

    if (n == 1)
        return left;

    if (n == 2)
    {
        if (coins[left] < coins[right])
            return left;
        else if (coins[right] < coins[left])
            return right;
        else
            return -1;
    }

    int half = n / 2;

    int leftStart = left;
    int leftEnd = left + half - 1;

    int rightStart = left + half;
    int rightEnd = left + 2 * half - 1;

    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = leftStart; i <= leftEnd; i++)
        leftWeight += coins[i];

    for (int i = rightStart; i <= rightEnd; i++)
        rightWeight += coins[i];

    if (leftWeight < rightWeight)
    {
        return findDefective(coins, leftStart, leftEnd);
    }
    else if (rightWeight < leftWeight)
    {
        return findDefective(coins, rightStart, rightEnd);
    }
    else
    {
        if (n % 2 == 0)
            return -1;

        int leftover = left + 2 * half;
        int normalCoin = leftStart;

        if (coins[leftover] < coins[normalCoin])
            return leftover;

        return -1;
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    if (n <= 0)
        return 1;

    if (n == 1)
    {
        printf("Cannot determine with only one coin.\n");
        return 0;
    }

    int *coins = malloc(n * sizeof(int));

    if (coins == NULL)
        return 1;

    printf("Enter weights:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Coin %d: ", i + 1);
        scanf("%d", &coins[i]);
    }

    int defective = findDefective(coins, 0, n - 1);

    if (defective == -1)
        printf("No defective coin exists.\n");
    else
        printf("Defective coin: Coin %d\n", defective + 1);

    free(coins);

    return 0;
}
