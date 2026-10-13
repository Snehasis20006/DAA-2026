/* Q6: Reorganize a string so equal characters are at least K positions apart.
   Greedy choice: at each position, use the available character with greatest remaining count. */
#include <stdio.h>
#include <string.h>
#define MAXLEN 1000
#define CHARSET 256

int main(void) {
    char s[MAXLEN + 1], result[MAXLEN + 1];
    int count[CHARSET] = {0}, last[CHARSET], i, pos, n, K;
    printf("Enter a string without spaces: ");
    if (scanf("%1000s", s) != 1) { printf("Invalid input.\n"); return 1; }
    printf("Enter K: ");
    if (scanf("%d", &K) != 1 || K < 0) { printf("Invalid K.\n"); return 1; }
    n = (int)strlen(s);
    for (i = 0; i < CHARSET; i++) last[i] = -1000000;
    for (i = 0; i < n; i++) count[(unsigned char)s[i]]++;

    for (pos = 0; pos < n; pos++) {
        int c, best = -1;
        for (c = 0; c < CHARSET; c++) {
            if (count[c] > 0 && pos - last[c] >= K) {
                if (best == -1 || count[c] > count[best]) best = c;
            }
        }
        if (best == -1) {
            printf("No valid arrangement exists (empty string).\n");
            printf("Time complexity: O(n * 256); space complexity: O(n + 256).\n");
            return 0;
        }
        result[pos] = (char)best;
        count[best]--;
        last[best] = pos;
    }
    result[n] = '\0';
    printf("Reorganized string: %s\n", result);
    printf("Time complexity: O(n * 256); space complexity: O(n + 256).\n");
    return 0;
}
