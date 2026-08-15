#include <stdio.h>
#include <stdlib.h>

void addMatrix(int n, long long A[][n], long long B[][n],
               long long C[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtractMatrix(int n, long long A[][n], long long B[][n],
                    long long C[][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, long long A[][n], long long B[][n],
              long long C[][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    long long (*A11)[k] = malloc(k * sizeof(*A11));
    long long (*A12)[k] = malloc(k * sizeof(*A12));
    long long (*A21)[k] = malloc(k * sizeof(*A21));
    long long (*A22)[k] = malloc(k * sizeof(*A22));

    long long (*B11)[k] = malloc(k * sizeof(*B11));
    long long (*B12)[k] = malloc(k * sizeof(*B12));
    long long (*B21)[k] = malloc(k * sizeof(*B21));
    long long (*B22)[k] = malloc(k * sizeof(*B22));

    long long (*M1)[k] = malloc(k * sizeof(*M1));
    long long (*M2)[k] = malloc(k * sizeof(*M2));
    long long (*M3)[k] = malloc(k * sizeof(*M3));
    long long (*M4)[k] = malloc(k * sizeof(*M4));
    long long (*M5)[k] = malloc(k * sizeof(*M5));
    long long (*M6)[k] = malloc(k * sizeof(*M6));
    long long (*M7)[k] = malloc(k * sizeof(*M7));

    long long (*T1)[k] = malloc(k * sizeof(*T1));
    long long (*T2)[k] = malloc(k * sizeof(*T2));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(k, A11, A22, T1);
    addMatrix(k, B11, B22, T2);
    strassen(k, T1, T2, M1);

    // M2 = (A21 + A22)B11
    addMatrix(k, A21, A22, T1);
    strassen(k, T1, B11, M2);

    // M3 = A11(B12 - B22)
    subtractMatrix(k, B12, B22, T2);
    strassen(k, A11, T2, M3);

    // M4 = A22(B21 - B11)
    subtractMatrix(k, B21, B11, T2);
    strassen(k, A22, T2, M4);

    // M5 = (A11 + A12)B22
    addMatrix(k, A11, A12, T1);
    strassen(k, T1, B22, M5);

    // M6 = (A21 - A11)(B11 + B12)
    subtractMatrix(k, A21, A11, T1);
    addMatrix(k, B11, B12, T2);
    strassen(k, T1, T2, M6);

    // M7 = (A12 - A22)(B21 + B22)
    subtractMatrix(k, A12, A22, T1);
    addMatrix(k, B21, B22, T2);
    strassen(k, T1, T2, M7);

    // C11 = M1 + M4 - M5 + M7
    // C12 = M3 + M5
    // C21 = M2 + M4
    // C22 = M1 - M2 + M3 + M6

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                M1[i][j] + M4[i][j] -
                M5[i][j] + M7[i][j];

            C[i][j + k] =
                M3[i][j] + M5[i][j];

            C[i + k][j] =
                M2[i][j] + M4[i][j];

            C[i + k][j + k] =
                M1[i][j] - M2[i][j] +
                M3[i][j] + M6[i][j];
        }
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);

    free(B11);
    free(B12);
    free(B21);
    free(B22);

    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);

    free(T1);
    free(T2);
}

int main()
{
    int n;

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    if (n <= 0 || (n & (n - 1)) != 0)
    {
        printf("Matrix size must be a power of 2.\n");
        return 1;
    }

    long long (*A)[n] = malloc(n * sizeof(*A));
    long long (*B)[n] = malloc(n * sizeof(*B));
    long long (*C)[n] = malloc(n * sizeof(*C));

    printf("Enter matrix A:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &A[i][j]);

    printf("Enter matrix B:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &B[i][j]);

    strassen(n, A, B, C);

    printf("\nResult matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lld ", C[i][j]);

        printf("\n");
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
