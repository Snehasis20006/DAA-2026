#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(arr[mid] == key)
            return 1;

        if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x, i;

    printf("Enter n: ");
    scanf("%d", &n);

    int S1[100], S2[100];

    printf("Enter S1:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter S2:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter x: ");
    scanf("%d", &x);

    qsort(S2, n, sizeof(int), compare);

    for(i = 0; i < n; i++)
    {
        int need = x - S1[i];

        if(binarySearch(S2, n, need))
        {
            printf("Pair Found: %d + %d = %d\n",
                   S1[i], need, x);
            return 0;
        }
    }

    printf("No Pair Exists\n");

    return 0;
}