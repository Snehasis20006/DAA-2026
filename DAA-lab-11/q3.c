
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100002
#define MAXL 10
#define HASH_SIZE 262147

char words[MAXN][MAXL + 1];

int hashTable[HASH_SIZE];
int distA[MAXN];
int distB[MAXN];

int frontA[MAXN], frontB[MAXN];
int nextA[MAXN], nextB[MAXN];

int N, L, totalWords;

// Calculate hash value of a word
unsigned int hashWord(const char *s)
{
    unsigned int hash = 5381;

    while (*s)
    {
        hash = ((hash << 5) + hash) + (unsigned char)*s;
        s++;
    }

    return hash % HASH_SIZE;
}

// Find a word in the hash table
int findWord(const char *s)
{
    unsigned int index = hashWord(s);

    while (hashTable[index] != 0)
    {
        int id = hashTable[index] - 1;

        if (strcmp(words[id], s) == 0)
            return id;

        index++;

        if (index == HASH_SIZE)
            index = 0;
    }

    return -1;
}

// Insert a word into the hash table
int insertWord(const char *s)
{
    int id = findWord(s);

    if (id != -1)
        return id;

    id = totalWords++;

    strcpy(words[id], s);

    unsigned int index = hashWord(s);

    while (hashTable[index] != 0)
    {
        index++;

        if (index == HASH_SIZE)
            index = 0;
    }

    hashTable[index] = id + 1;

    return id;
}

// Validate lowercase English word
int validWord(const char *s)
{
    int len = strlen(s);

    if (len != L)
        return 0;

    int i;

    for (i = 0; i < len; i++)
    {
        if (s[i] < 'a' || s[i] > 'z')
            return 0;
    }

    return 1;
}

// Expand one complete BFS level
// Returns shortest distance if searches meet, otherwise -1
int expandLevel(
    int current[],
    int *currentSize,
    int next[],
    int *nextSize,
    int dist[],
    int otherDist[]
)
{
    int best = INT_MAX;

    int i, pos, id;
    char temp[MAXL + 1];

    *nextSize = 0;

    for (i = 0; i < *currentSize; i++)
    {
        int u = current[i];

        strcpy(temp, words[u]);

        // Try changing each character
        for (pos = 0; pos < L; pos++)
        {
            char original = temp[pos];

            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c == original)
                    continue;

                temp[pos] = c;

                // Check whether the new word exists
                id = findWord(temp);

                if (id != -1)
                {
                    // Check if the opposite BFS has reached it
                    if (otherDist[id] != -1)
                    {
                        int candidate =
                            dist[u] + 1 + otherDist[id];

                        if (candidate < best)
                            best = candidate;
                    }

                    // Visit this word only once in this search
                    if (dist[id] == -1)
                    {
                        dist[id] = dist[u] + 1;

                        next[(*nextSize)++] = id;
                    }
                }
            }

            // Restore original character
            temp[pos] = original;
        }
    }

    *currentSize = *nextSize;

    for (i = 0; i < *nextSize; i++)
        current[i] = next[i];

    if (best != INT_MAX)
        return best;

    return -1;
}

// Bidirectional BFS algorithm
int bidirectionalBFS(int start, int target)
{
    int sizeA = 1;
    int sizeB = 1;

    int nextSizeA, nextSizeB;

    int i;

    for (i = 0; i < totalWords; i++)
    {
        distA[i] = -1;
        distB[i] = -1;
    }

    // Starting points of both searches
    frontA[0] = start;
    frontB[0] = target;

    distA[start] = 0;
    distB[target] = 0;

    if (start == target)
        return 0;

    // Continue until one search has no more vertices
    while (sizeA > 0 && sizeB > 0)
    {
        int answer;

        // Expand the smaller BFS frontier
        if (sizeA <= sizeB)
        {
            answer = expandLevel(
                frontA, &sizeA,
                nextA, &nextSizeA,
                distA, distB
            );
        }
        else
        {
            answer = expandLevel(
                frontB, &sizeB,
                nextB, &nextSizeB,
                distB, distA
            );
        }

        if (answer != -1)
            return answer;
    }

    // No transformation path exists
    return -1;
}

int main()
{
    int i;
    char A[MAXL + 2];
    char B[MAXL + 2];
    char input[MAXL + 2];

    printf("Enter number of dictionary words: ");
    scanf("%d", &N);

    if (N < 1 || N > 100000)
    {
        printf("Invalid number of words.\n");
        return 0;
    }

    // Read first word to determine word length
    printf("Enter dictionary words:\n");

    scanf("%11s", input);

    L = strlen(input);

    if (L < 1 || L > MAXL)
    {
        printf("Invalid word length.\n");
        return 0;
    }

    if (!validWord(input))
    {
        printf("Invalid dictionary word.\n");
        return 0;
    }

    insertWord(input);

    // Read remaining dictionary words
    for (i = 1; i < N; i++)
    {
        scanf("%11s", input);

        if (!validWord(input))
        {
            printf("Invalid dictionary word.\n");
            return 0;
        }

        if (findWord(input) != -1)
        {
            printf("Duplicate dictionary word.\n");
            return 0;
        }

        insertWord(input);
    }

    // Read starting and target words
    printf("Enter starting word A: ");
    scanf("%11s", A);

    printf("Enter target word B: ");
    scanf("%11s", B);

    if (!validWord(A) || !validWord(B))
    {
        printf("Invalid starting or target word.\n");
        return 0;
    }

    // Target word must exist in dictionary
    int target = findWord(B);

    if (target == -1)
    {
        printf("Target word is not present in dictionary.\n");
        return 0;
    }

    // Starting word may or may not exist in dictionary
    int start = findWord(A);

    if (start == -1)
        start = insertWord(A);

    // Find minimum transformations
    int result = bidirectionalBFS(start, target);

    printf("\nMinimum number of mutations: %d\n", result);

    if (result == -1)
        printf("No valid transformation sequence exists.\n");
    else
        printf("A valid transformation exists.\n");

    return 0;
}
// output-----------------------------
//Enter number of dictionary words: 6
// Enter dictionary words:
// hot
// dot
// dog
// lot
// log
// cog
// Enter starting word A: hit
// Enter target word B: cog


// 4. Expected output
// Minimum number of mutations: 4
// A valid transformation exists.