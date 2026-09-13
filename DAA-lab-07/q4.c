#include <stdio.h>

long long minimumMoves(int n)
{
    long long t;

    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    t = minimumMoves(n - 1);

    if (n % 2 == 0)
        return 2 * t;
    else
        return 2 * t + 1;
}

int main()
{
    int n;
    long long result;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n > 60)
    {
        printf("Invalid input.\n");
        return 0;
    }

    result = minimumMoves(n);

    printf("\nMinimum number of moves = %lld\n", result);

    return 0;
}