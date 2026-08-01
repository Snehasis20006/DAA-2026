#include <stdio.h>

int main()
{
    int a[100];
    int n, i, j;
    int duplicate = 0;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(a[i] == a[j])
            {
                duplicate = 1;
                printf("Duplicate element found: %d\n", a[i]);
                break;
            }
        }

        if(duplicate == 1)
        {
            break;
        }
    }

    if(duplicate == 0)
    {
        printf("All elements are unique.\n");
    }

    return 0;
}