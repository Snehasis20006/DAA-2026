#include <stdio.h>

struct Event
{
    int point;
    int type;
};

void sortEvents(struct Event events[], int n)
{
    int i, j;
    struct Event temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(events[j].point > events[j + 1].point)
            {
                temp = events[j];
                events[j] = events[j + 1];
                events[j + 1] = temp;
            }
            else if(events[j].point == events[j + 1].point &&
                    events[j].type < events[j + 1].type)
            {
                temp = events[j];
                events[j] = events[j + 1];
                events[j + 1] = temp;
            }
        }
    }
}

int main()
{
    struct Event events[200];

    int n;
    int i;
    int left, right;
    int current = 0;
    int maximum = 0;
    int bestPoint = 0;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number of intervals.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        printf("Enter left and right endpoints of interval %d: ", i + 1);
        scanf("%d %d", &left, &right);

        events[2 * i].point = left;
        events[2 * i].type = 1;

        events[2 * i + 1].point = right;
        events[2 * i + 1].type = -1;
    }

    sortEvents(events, 2 * n);

    for(i = 0; i < 2 * n; i++)
    {
        if(events[i].type == 1)
        {
            current++;

            if(current > maximum)
            {
                maximum = current;
                bestPoint = events[i].point;
            }
        }
        else
        {
            current--;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", bestPoint);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}