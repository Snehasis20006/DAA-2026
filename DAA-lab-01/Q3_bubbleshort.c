#include <stdio.h>

#define MAX 100

void copyArray(int source[], int dest[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        dest[i] = source[i];
}

void printArray(int arr[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int bubbleSortEarly(int arr[], int n)
{
    int i, j, temp;
    int comparisons = 0;
    int swapped;

    for(i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return comparisons;
}

int bubbleSortNormal(int arr[], int n)
{
    int i, j, temp;
    int comparisons = 0;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main()
{
    int original[MAX];
    int arr1[MAX];
    int arr2[MAX];
    int n, i;
    int earlyComp, normalComp;

    printf("Enter number of elements (Maximum %d): ", MAX);
    scanf("%d", &n);

    if(n > MAX || n <= 0)
    {
        printf("Invalid size!\n");
        return 0;
    }

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++)
        scanf("%d", &original[i]);

    copyArray(original, arr1, n);
    copyArray(original, arr2, n);

    earlyComp = bubbleSortEarly(arr1, n);
    normalComp = bubbleSortNormal(arr2, n);

    printf("\nSorted Array (Early Bubble Sort):\n");
    printArray(arr1, n);
    printf("Comparisons = %d\n", earlyComp);

    printf("\nSorted Array (Normal Bubble Sort):\n");
    printArray(arr2, n);
    printf("Comparisons = %d\n", normalComp);

    printf("\nComparison Result\n");
    printf("-----------------\n");
    printf("Early Bubble Sort Comparisons : %d\n", earlyComp);
    printf("Normal Bubble Sort Comparisons: %d\n", normalComp);

    if(earlyComp < normalComp)
        printf("Early Bubble Sort is more efficient.\n");
    else if(earlyComp == normalComp)
        printf("Both versions performed the same number of comparisons.\n");
    else
        printf("Normal Bubble Sort is more efficient.\n");

    return 0;
}