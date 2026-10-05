#include <stdio.h>
#include <string.h>

int main()
{
    char X[100], Y[100];
    int L[101][101];
    int m, n;
    int i, j;
    int index;
    char lcs[100];

    printf("Enter first sequence: ");
    scanf("%s", X);

    printf("Enter second sequence: ");
    scanf("%s", Y);

    m = strlen(X);
    n = strlen(Y);

    /* Build the LCS table */
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                L[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            else
            {
                if (L[i - 1][j] > L[i][j - 1])
                    L[i][j] = L[i - 1][j];
                else
                    L[i][j] = L[i][j - 1];
            }
        }
    }

    /* Length of LCS */
    printf("\nLength of LCS = %d\n", L[m][n]);

    /* Reconstruct the LCS */
    index = L[m][n];
    lcs[index] = '\0';

    i = m;
    j = n;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("Longest Common Subsequence = %s\n", lcs);

    return 0;
}
// sample output:
// Enter first sequence: tyhj
// Enter second sequence: hjty

// Length of LCS = 2
// Longest Common Subsequence = hj