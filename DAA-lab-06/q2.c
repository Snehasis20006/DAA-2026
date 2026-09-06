#include <stdio.h>
#include <math.h>

#define MAX 20

void addition(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplication(int A[MAX][MAX], int B[MAX][MAX],
                    int C[MAX][MAX], int n)
{
    int i, j, k;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for(k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int isZeroMatrix(int A[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

int isSymmetric(int A[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

double determinant(int A[MAX][MAX], int n)
{
    double temp[MAX][MAX];
    double det = 1.0;
    int i, j, k;
    int sign = 1;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            temp[i][j] = A[i][j];
        }
    }

    for(i = 0; i < n; i++)
    {
        if(fabs(temp[i][i]) < 0.000001)
        {
            for(k = i + 1; k < n; k++)
            {
                if(fabs(temp[k][i]) > 0.000001)
                {
                    for(j = 0; j < n; j++)
                    {
                        double x = temp[i][j];
                        temp[i][j] = temp[k][j];
                        temp[k][j] = x;
                    }

                    sign = -sign;
                    break;
                }
            }
        }

        if(fabs(temp[i][i]) < 0.000001)
            return 0;

        for(k = i + 1; k < n; k++)
        {
            double factor = temp[k][i] / temp[i][i];

            for(j = i; j < n; j++)
            {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }

    for(i = 0; i < n; i++)
        det *= temp[i][i];

    return sign * det;
}

void transposeInPlace(int A[MAX][MAX], int n)
{
    int i, j, temp;

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

void printMatrix(int A[MAX][MAX], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, i, j;

    printf("Enter size of matrix: ");
    scanf("%d", &n);

    printf("Enter Matrix A:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter Matrix B:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    printf("\nMatrix Addition:\n");
    addition(A, B, C, n);
    printMatrix(C, n);

    printf("\nMatrix Multiplication:\n");
    multiplication(A, B, C, n);
    printMatrix(C, n);

    if(isZeroMatrix(A, n))
        printf("\nA is a zero matrix.\n");
    else
        printf("\nA is not a zero matrix.\n");

    if(isSymmetric(A, n))
        printf("A is symmetric.\n");
    else
        printf("A is not symmetric.\n");

    printf("\nDeterminant of A = %.2f\n", determinant(A, n));

    transposeInPlace(A, n);

    printf("\nTranspose of A:\n");
    printMatrix(A, n);

    return 0;
}