#include <stdio.h>

#define MAX 20

long long dp[MAX + 1];
int split[MAX];

void threePegHanoi(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    threePegHanoi(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    threePegHanoi(n - 1, auxiliary, destination, source);
}

void fourPegHanoi(int n, char source, char destination,
                  char aux1, char aux2)
{
    int k;

    if (n == 0)
        return;

    k = split[n];

    /* Move k disks using 4 pegs */
    fourPegHanoi(k, source, aux1, destination, aux2);

    /* Move remaining disks using 3 pegs */
    threePegHanoi(n - k, source, destination, aux2);

    /* Move k disks to destination */
    fourPegHanoi(k, aux1, destination, source, aux2);
}

int main()
{
    int n;
    int i, k;
    long long moves;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Enter disks between 1 and %d.\n", MAX);
        return 0;
    }

    dp[0] = 0;
    dp[1] = 1;
    split[1] = 1;

    for (i = 2; i <= n; i++)
    {
        dp[i] = 999999999;

        for (k = 1; k < i; k++)
        {
            moves = 2 * dp[k];

            moves = moves + ((1LL << (i - k)) - 1);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n", dp[n]);

    printf("\nMoves:\n");

    fourPegHanoi(n, 'A', 'D', 'B', 'C');

    return 0;
}