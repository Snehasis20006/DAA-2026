#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int a[], int low, int high)
{
    int i, j, pivot, temp;

    i = low;
    j = high;
    pivot = a[(low + high) / 2];

    while(i <= j)
    {
        while(a[i] < pivot)
            i++;

        while(a[j] > pivot)
            j--;

        if(i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }

    if(low < j)
        quickSort(a, low, j);

    if(i < high)
        quickSort(a, i, high);
}

int main()
{
    int a[1000];
    int n, i;

    FILE *fp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    srand((unsigned)time(NULL));

    /* Create and write random elements to file */

    fp = fopen("input.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    printf("\nRandom elements stored in input.txt\n");

    /* Read elements from file */

    fp = fopen("input.txt", "r");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    printf("\nElements before sorting:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    quickSort(a, 0, n - 1);

    printf("\n\nElements after Quick Sort:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}