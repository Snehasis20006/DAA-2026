/* Q7: Minimize deviation. Odd values are doubled first; repeatedly halve the maximum even value. */
#include <stdio.h>
#define MAXN 100000

void push(long long h[], int *n, long long x) {
    int i = ++(*n);
    while (i > 1 && h[i / 2] < x) { h[i] = h[i / 2]; i /= 2; }
    h[i] = x;
}
long long popMax(long long h[], int *n) {
    long long result = h[1], last = h[(*n)--];
    int i = 1, c;
    while (i * 2 <= *n) {
        c = i * 2;
        if (c + 1 <= *n && h[c + 1] > h[c]) c++;
        if (last >= h[c]) break;
        h[i] = h[c]; i = c;
    }
    if (*n > 0) h[i] = last;
    return result;
}
int main(void) {
    int n, i, size = 0;
    long long heap[MAXN + 2], minValue = 0, best;
    printf("Enter array size (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid input.\n"); return 1; }
    for (i = 0; i < n; i++) {
        long long x;
        printf("Enter positive integer %d: ", i + 1);
        if (scanf("%lld", &x) != 1 || x <= 0 || x > 4000000000000000000LL) {
            printf("Invalid value.\n"); return 1;
        }
        if (x % 2 != 0) x *= 2;
        if (i == 0 || x < minValue) minValue = x;
        push(heap, &size, x);
    }
    best = heap[1] - minValue;
    while (heap[1] % 2 == 0) {
        long long largest = popMax(heap, &size);
        largest /= 2;
        if (largest < minValue) minValue = largest;
        push(heap, &size, largest);
        if (heap[1] - minValue < best) best = heap[1] - minValue;
    }
    printf("Minimum deviation: %lld\n", best);
    printf("Time complexity: O(n log M), where M is the largest normalized value; space complexity: O(n).\n");
    return 0;
}
