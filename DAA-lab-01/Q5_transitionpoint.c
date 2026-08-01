#include <stdio.h>

int main()
{
    int a[100];
    int n;
    int i;
    int low, high, mid;
    int ans = -1;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements (0 and 1 only):\n", n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    low = 0;
    high = n - 1;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(a[mid] == 1)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if(ans == -1)
    {
        printf("No partition point found (All elements are 0).\n");
    }
    else
    {
        printf("Partition Point = %d\n", ans);
        printf("First 1 is at index %d\n", ans);
    }

    return 0;
}