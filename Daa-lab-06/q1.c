#include <stdio.h>

int partition(int a[], int low, int high)
{
    int pivot, i, j, temp;

    pivot = a[high];
    i = low - 1;

    for(j = low; j < high; j++)
    {
        if(a[j] <= pivot)
        {
            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

int quickSelect(int a[], int low, int high, int k)
{
    int p;

    if(low == high)
        return a[low];

    p = partition(a, low, high);

    if(k == p)
        return a[p];

    if(k < p)
        return quickSelect(a, low, p - 1, k);

    return quickSelect(a, p + 1, high, k);
}

int main()
{
    int a[1000];
    int n, i;
    int left, right;
    float median;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if(n % 2 != 0)
    {
        median = quickSelect(a, 0, n - 1, n / 2);

        printf("Median = %.2f\n", median);
    }
    else
    {
        left = quickSelect(a, 0, n - 1, n / 2 - 1);
        right = quickSelect(a, 0, n - 1, n / 2);

        median = (left + right) / 2.0;

        printf("Median = %.2f\n", median);
    }

    return 0;
}