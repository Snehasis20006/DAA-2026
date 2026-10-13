/* Q3: Minimum refuelling stops using a max-heap of reachable fuel amounts. */
#include <stdio.h>

#define MAXN 1000

void push(int heap[], int *size, int value) {
    int i = ++(*size);
    while (i > 1 && heap[i / 2] < value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = value;
}
int popMax(int heap[], int *size) {
    int result = heap[1], last = heap[(*size)--], i = 1, child;
    while (i * 2 <= *size) {
        child = i * 2;
        if (child + 1 <= *size && heap[child + 1] > heap[child]) child++;
        if (last >= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    if (*size > 0) heap[i] = last;
    return result;
}

int main(void) {
    int n, i, stops = 0, heap[MAXN + 2], size = 0;
    int d[MAXN], f[MAXN];
    long long fuel, D;

    printf("Enter target distance D and initial fuel F: ");
    if (scanf("%lld %lld", &D, &fuel) != 2 || D < 0 || fuel < 0) {
        printf("Invalid input.\n"); return 1;
    }
    printf("Enter number of stations (0-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 0 || n > MAXN) {
        printf("Invalid number of stations.\n"); return 1;
    }
    for (i = 0; i < n; i++) {
        printf("Enter distance and fuel amount for station %d: ", i + 1);
        if (scanf("%d %d", &d[i], &f[i]) != 2 || d[i] < 0 || f[i] < 0) {
            printf("Invalid station data.\n"); return 1;
        }
    }
    /* Sort stations by distance. */
    for (i = 0; i < n - 1; i++) {
        int j;
        for (j = 0; j < n - 1 - i; j++) if (d[j] > d[j + 1]) {
            int temp = d[j]; d[j] = d[j + 1]; d[j + 1] = temp;
            temp = f[j]; f[j] = f[j + 1]; f[j + 1] = temp;
        }
    }

    for (i = 0; i <= n; i++) {
        long long next = (i == n) ? D : d[i];
        if (next > D) { printf("Station lies beyond target; ignoring it.\n"); continue; }
        while (fuel < next) {
            if (size == 0) {
                printf("Target is unreachable.\n");
                return 0;
            }
            fuel += popMax(heap, &size);
            stops++;
        }
        if (i < n) push(heap, &size, f[i]);
    }
    printf("Minimum number of refuelling stops: %d\n", stops);
    printf("Time complexity: O(n^2) including station sorting; space complexity: O(n).\n");
    return 0;
}
