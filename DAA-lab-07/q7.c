#include <stdio.h>

#define MAX 50

long long m[MAX][MAX];
int split[MAX][MAX];

void printParenthesis(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printParenthesis(i, split[i][j]);

    printf(" x ");

    printParenthesis(split[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;
    int p[MAX];
    int i, j, k, length;

    long long cost;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of matrices.\n");
        return 0;
    }

    printf("\nEnter dimensions:\n");

    printf("Enter p0: ");
    scanf("%d", &p[0]);

    for (i = 1; i <= n; i++)
    {
        printf("Enter p%d: ", i);
        scanf("%d", &p[i]);
    }

    /*
       Cost of multiplying one matrix is zero.
    */
    for (i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    /*
       length = number of matrices in the chain
    */
    for (length = 2; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;

            m[i][j] = 9223372036854775807LL;

            for (k = i; k < j; k++)
            {
                cost = m[i][k]
                     + m[k + 1][j]
                     + (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %lld\n",
           m[1][n]);

    printf("Optimal parenthesization = ");

    printParenthesis(1, n);

    printf("\n");

    return 0;
}