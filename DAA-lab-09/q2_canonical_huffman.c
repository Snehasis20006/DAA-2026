/* Q2: Huffman Coding and canonical codebook. Standard C; maximum 60 symbols. */
#include <stdio.h>
#include <string.h>

#define MAXN 60
#define MAXNODE (2 * MAXN)

typedef struct {
    char symbol;
    long long freq;
    int left, right, parent;
} Node;

typedef struct {
    char symbol;
    int length;
} CodeInfo;

Node tree[MAXNODE];
int lengths[MAXN];

void findLengths(int node, int depth) {
    if (tree[node].left == -1 && tree[node].right == -1) {
        lengths[node] = (depth == 0) ? 1 : depth;
        return;
    }
    if (tree[node].left != -1) findLengths(tree[node].left, depth + 1);
    if (tree[node].right != -1) findLengths(tree[node].right, depth + 1);
}

void sortCodes(CodeInfo a[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (a[j].length > a[j + 1].length ||
                (a[j].length == a[j + 1].length && a[j].symbol > a[j + 1].symbol)) {
                CodeInfo temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void printBinary(unsigned long long code, int len) {
    int i;
    for (i = len - 1; i >= 0; i--) putchar((code & (1ULL << i)) ? '1' : '0');
}

int main(void) {
    int n, i, nodeCount, used = 0;
    CodeInfo info[MAXN];
    unsigned long long code = 0;
    int previousLength;

    printf("Enter number of symbols (2-%d): ", MAXN);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAXN) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    nodeCount = n;
    for (i = 0; i < n; i++) {
        printf("Enter one character and its positive frequency for symbol %d: ", i + 1);
        if (scanf(" %c %lld", &tree[i].symbol, &tree[i].freq) != 2 || tree[i].freq <= 0) {
            printf("Invalid symbol/frequency.\n");
            return 1;
        }
        tree[i].left = tree[i].right = tree[i].parent = -1;
    }

    while (used < n - 1) {
        int first = -1, second = -1;
        for (i = 0; i < nodeCount; i++) {
            if (tree[i].parent != -1) continue;
            if (first == -1 || tree[i].freq < tree[first].freq) {
                second = first;
                first = i;
            } else if (second == -1 || tree[i].freq < tree[second].freq) {
                second = i;
            }
        }
        if (first == -1 || second == -1) {
            printf("Could not construct Huffman tree.\n");
            return 1;
        }
        tree[nodeCount].symbol = '\0';
        tree[nodeCount].freq = tree[first].freq + tree[second].freq;
        tree[nodeCount].left = first;
        tree[nodeCount].right = second;
        tree[nodeCount].parent = -1;
        tree[first].parent = nodeCount;
        tree[second].parent = nodeCount;
        nodeCount++;
        used++;
    }

    /* Find each leaf's depth by following its parent links. */
    for (i = 0; i < n; i++) {
        int p = i, depth = 0;
        while (tree[p].parent != -1) {
            depth++;
            p = tree[p].parent;
        }
        info[i].symbol = tree[i].symbol;
        info[i].length = (depth == 0) ? 1 : depth;
    }
    sortCodes(info, n);

    printf("\nCanonical Huffman codebook (by length, then character):\n");
    code = 0;
    previousLength = info[0].length;
    printf("%c : ", info[0].symbol);
    printBinary(code, previousLength);
    putchar('\n');

    for (i = 1; i < n; i++) {
        int shift = info[i].length - previousLength;
        code = (code + 1ULL) << shift;
        if (info[i].length > 63) {
            printf("Code length exceeds this program's 64-bit limit.\n");
            return 1;
        }
        printf("%c : ", info[i].symbol);
        printBinary(code, info[i].length);
        putchar('\n');
        previousLength = info[i].length;
    }

    printf("Time complexity: O(n^2) for tree construction; space complexity: O(n).\n");
    return 0;
}
