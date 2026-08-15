#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int min;
    int max;
} Result;

Result findMinMax(int a[], int low, int high)
{
    Result result, left, right;

    // Only one element
    if (low == high)
    {
        result.min = a[low];
        result.max = a[low];
        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        if (a[low] < a[high])
        {
            result.min = a[low];
            result.max = a[high];
        }
        else
        {
            result.min = a[high];
            result.max = a[low];
        }

        return result;
    }

    int mid = (low + high) / 2;

    left = findMinMax(a, low, mid);
    right = findMinMax(a, mid + 1, high);

    result.min = (left.min < right.min) ? left.min : right.min;
    result.max = (left.max > right.max) ? left.max : right.max;

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    Result result = findMinMax(a, 0, n - 1);

    printf("Minimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);

    free(a);

    return 0;
}
