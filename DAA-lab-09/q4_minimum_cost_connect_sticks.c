/* Q4: Minimum cost to connect sticks using a min-heap. */
#include <stdio.h>
#define MAXN 1000

void push(long long h[], int *n, long long x) {
    int i = ++(*n);
    while (i > 1 && h[i / 2] > x) { h[i] = h[i / 2]; i /= 2; }
    h[i] = x;
}
long long popMin(long long h[], int *n) {
    long long result = h[1], last = h[(*n)--];
    int i = 1, c;
    while (i * 2 <= *n) {
        c = i * 2;
        if (c + 1 <= *n && h[c + 1] < h[c]) c++;
        if (last <= h[c]) break;
        h[i] = h[c]; i = c;
    }
    if (*n > 0) h[i] = last;
    return result;
}
int main(void) {
    int n, i, size = 0;
    long long heap[MAXN + 2], total = 0;
    printf("Enter number of sticks (1-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) { printf("Invalid input.\n"); return 1; }
    for (i = 0; i < n; i++) {
        long long x;
        printf("Enter length of stick %d: ", i + 1);
        if (scanf("%lld", &x) != 1 || x < 0) { printf("Invalid length.\n"); return 1; }
        push(heap, &size, x);
    }
    while (size > 1) {
        long long a = popMin(heap, &size), b = popMin(heap, &size), sum = a + b;
        printf("Connect %lld and %lld: cost = %lld\n", a, b, sum);
        total += sum;
        push(heap, &size, sum);
    }
    printf("Minimum total cost: %lld\n", total);
    printf("Time complexity: O(n log n); space complexity: O(n).\n");
    return 0;
}
