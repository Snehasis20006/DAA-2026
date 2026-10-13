/* Q8: Minimum meeting rooms using sorted start and end times. */
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000

int compareInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int n, i, starts[MAXN], ends[MAXN], s = 0, e = 0, rooms = 0, maximum = 0;
    printf("Enter number of meetings (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid input.\n"); return 1; }
    for (i = 0; i < n; i++) {
        printf("Enter start and end time for meeting %d: ", i + 1);
        if (scanf("%d %d", &starts[i], &ends[i]) != 2 || starts[i] > ends[i]) {
            printf("Invalid interval.\n"); return 1;
        }
    }
    qsort(starts, n, sizeof(int), compareInt);
    qsort(ends, n, sizeof(int), compareInt);
    while (s < n) {
        if (s < n && (e == n || starts[s] < ends[e])) {
            rooms++;
            if (rooms > maximum) maximum = rooms;
            s++;
        } else {
            rooms--;
            e++;
        }
    }
    printf("Minimum number of meeting rooms: %d\n", maximum);
    printf("Time complexity: O(n log n); space complexity: O(n).\n");
    return 0;
}
