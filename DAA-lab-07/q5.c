#include <stdio.h>

int main()
{
    int n;
    int possible[100];
    int next[100];
    int i, j;
    int shots[200];
    int shotCount = 0;
    int remaining;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1 || n > 99)
    {
        printf("Invalid input. n must be greater than 1.\n");
        return 0;
    }

    /* Initially target can be anywhere */
    for (i = 0; i < n; i++)
        possible[i] = 1;

    /*
       Construct shooting sequence
    */

    if (n == 2)
    {
        shots[shotCount++] = 0;
        shots[shotCount++] = 0;
    }
    else if (n % 2 == 1)
    {
        /*
           For odd n, repeat a complete sweep.
           Two sweeps are sufficient for validation.
        */
        for (i = 0; i < n; i++)
            shots[shotCount++] = i;

        for (i = 0; i < n; i++)
            shots[shotCount++] = i;
    }
    else
    {
        /*
           For even n:
           2,3,...,n-1,n-1,...,3,2
        */
        for (i = 1; i <= n - 2; i++)
            shots[shotCount++] = i;

        for (i = n - 2; i >= 1; i--)
            shots[shotCount++] = i;
    }

    printf("\nShooting sequence:\n");

    for (i = 0; i < shotCount; i++)
        printf("%d ", shots[i] + 1);

    printf("\n\nChecking all possible target positions...\n");

    /*
       Simulate every shot.
       If target is at the shot position, that possibility is removed.
       Otherwise, target must move to an adjacent position.
    */

    for (i = 0; i < shotCount; i++)
    {
        for (j = 0; j < n; j++)
            next[j] = 0;

        for (j = 0; j < n; j++)
        {
            if (possible[j] == 1)
            {
                /* Target is hit */
                if (j == shots[i])
                    continue;

                /* Target moves left */
                if (j - 1 >= 0)
                    next[j - 1] = 1;

                /* Target moves right */
                if (j + 1 < n)
                    next[j + 1] = 1;
            }
        }

        for (j = 0; j < n; j++)
            possible[j] = next[j];
    }

    remaining = 0;

    for (i = 0; i < n; i++)
    {
        if (possible[i] == 1)
            remaining++;
    }

    if (remaining == 0)
        printf("Result: Target is guaranteed to be hit.\n");
    else
        printf("Result: Target may still be alive.\n");

    return 0;
}