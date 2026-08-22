#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int time;
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
            if(events[j].time > events[j + 1].time)
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
    int n, i;
    int entry, exit;
    int current = 0;
    int maximum = 0;
    int maximumTime = 0;

    struct Event events[200];

    printf("Enter number of people: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Number of people must be positive.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        printf("Enter entry and exit time for person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
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
                maximumTime = events[i].time;
            }
        }
        else
        {
            current--;
        }
    }

    printf("\nMaximum number of people present = %d\n", maximum);
    printf("Time when maximum people were present = %d\n", maximumTime);

    return 0;
}