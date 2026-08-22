#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n)
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int a[], int n, int value, int used[], int usedCount)
{
    int low = 0, high = n - 1;
    int i, mid;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(a[mid] == value)
        {
            /* Make sure this index is not already used */
            for(i = 0; i < usedCount; i++)
            {
                if(used[i] == mid)
                    break;
            }

            if(i == usedCount)
                return 1;
        }

        if(a[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int findSum(int a[], int n, int k, int T,
            int level, int start, int sum, int used[])
{
    int i;

    /* Choose k-1 elements */
    if(level == k - 1)
    {
        if(binarySearch(a, n, T - sum, used, k - 1))
            return 1;

        return 0;
    }

    for(i = start; i < n; i++)
    {
        used[level] = i;

        if(findSum(a, n, k, T, level + 1,
                   i + 1, sum + a[i], used))
            return 1;
    }

    return 0;
}

int main()
{
    int a[100];
    int used[100];
    int n, k, T;
    int i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    sort(a, n);

    if(findSum(a, n, k, T, 0, 0, 0, used))
        printf("YES, %d elements add up to %d\n", k, T);
    else
        printf("NO, %d elements do not add up to %d\n", k, T);

    return 0;
}