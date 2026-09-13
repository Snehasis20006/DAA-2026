#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    int *birth;
    int *death;
    int i;

    int left, right;
    int alive = 0;
    int maximum = 0;
    int bestYear = 0;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of scientists.\n");
        return 0;
    }

    birth = (int *)malloc(n * sizeof(int));
    death = (int *)malloc(n * sizeof(int));

    if (birth == NULL || death == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("\nEnter birth year and death year:\n");

    for (i = 0; i < n; i++)
    {
        printf("Scientist %d: ", i + 1);
        scanf("%d %d", &birth[i], &death[i]);
    }

    sort(birth, n);
    sort(death, n);

    left = 0;
    right = 0;

    while (left < n && right < n)
    {
        /*
           If birth year is smaller,
           birth event happens first.
        */
        if (birth[left] < death[right])
        {
            alive++;

            if (alive > maximum)
            {
                maximum = alive;
                bestYear = birth[left];
            }

            left++;
        }
        else
        {
            /*
               Death is processed first when
               birth year == death year.
            */
            alive--;
            right++;
        }
    }

    printf("\nYear with maximum number of scientists alive: %d\n",
           bestYear);

    printf("Maximum number of scientists alive: %d\n", maximum);

    free(birth);
    free(death);

    return 0;
}