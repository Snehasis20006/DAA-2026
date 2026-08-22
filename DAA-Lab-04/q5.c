#include <stdio.h>

struct Interval
{
    int start;
    int end;
};

void sortIntervals(struct Interval a[], int n)
{
    int i, j;
    struct Interval temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(a[j].start > a[j + 1].start)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    struct Interval a[100];
    struct Interval result[100];

    int n;
    int i;
    int count = 0;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number of intervals.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        printf("Enter start and end of interval %d: ", i + 1);
        scanf("%d %d", &a[i].start, &a[i].end);
    }

    sortIntervals(a, n);

    result[0] = a[0];
    count = 1;

    for(i = 1; i < n; i++)
    {
        if(a[i].start <= result[count - 1].end)
        {
            if(a[i].end > result[count - 1].end)
            {
                result[count - 1].end = a[i].end;
            }
        }
        else
        {
            result[count] = a[i];
            count++;
        }
    }

    printf("\nMerged intervals:\n");

    for(i = 0; i < count; i++)
    {
        printf("(%d, %d)\n", result[i].start, result[i].end);
    }

    return 0;
}