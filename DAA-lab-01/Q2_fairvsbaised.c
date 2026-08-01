#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n;
    int i;
    int fairHead = 0, fairTail = 0;
    int biasedHead = 0, biasedTail = 0;

    printf("Enter number of coin tosses: ");
    scanf("%d", &n);

    srand(time(NULL));

    // Fair Coin Simulation
    for(i = 0; i < n; i++)
    {
        if(rand() % 2 == 1)
            fairHead++;
        else
            fairTail++;
    }

    // Biased Coin Simulation (70%% HEAD)
    for(i = 0; i < n; i++)
    {
        int r = rand() % 100;

        if(r < 70)
            biasedHead++;
        else
            biasedTail++;
    }

    printf("\n===== Fair Coin =====\n");
    printf("Heads = %d\n", fairHead);
    printf("Tails = %d\n", fairTail);
    printf("Probability of Head = %.4f\n", (float)fairHead / n);
    printf("Probability of Tail = %.4f\n", (float)fairTail / n);

    printf("\n===== Biased Coin (70%% Head) =====\n");
    printf("Heads = %d\n", biasedHead);
    printf("Tails = %d\n", biasedTail);
    printf("Probability of Head = %.4f\n", (float)biasedHead / n);
    printf("Probability of Tail = %.4f\n", (float)biasedTail / n);

    return 0;
}