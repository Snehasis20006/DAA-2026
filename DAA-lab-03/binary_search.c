#include <stdio.h>

int binaryComparisons = 0;
int ternaryComparisons = 0;

int binarySearch(int arr[], int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        binaryComparisons++;

        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int ternarySearch(int arr[], int low, int high, int key)
{
    while (low <= high)
    {
        ternaryComparisons++;

        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (arr[mid1] == key)
            return mid1;

        if (arr[mid2] == key)
            return mid2;

        if (key < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (key > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    int n, key, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter sorted elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &key);

    int result1 = binarySearch(arr, n, key);
    int result2 = ternarySearch(arr, 0, n - 1, key);

    if (result1 != -1)
        printf("\nBinary Search: Element found at index %d\n", result1);
    else
        printf("\nBinary Search: Element not found\n");

    if (result2 != -1)
        printf("Ternary Search: Element found at index %d\n", result2);
    else
        printf("Ternary Search: Element not found\n");

    printf("\nNumber of Comparisons:\n");
    printf("Binary Search  = %d\n", binaryComparisons);
    printf("Ternary Search = %d\n", ternaryComparisons);

    return 0;
}