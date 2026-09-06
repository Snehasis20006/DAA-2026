#include <stdio.h>
#include <math.h>
#include <complex.h>
#include<stdlib.h>

#define PI 3.14159265358979323846

void fft(complex double a[], int n, int invert)
{
    int i, j;
    complex double *even, *odd;

    if(n == 1)
        return;

    even = (complex double *)malloc((n / 2) * sizeof(complex double));
    odd = (complex double *)malloc((n / 2) * sizeof(complex double));

    for(i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    for(i = 0; i < n / 2; i++)
    {
        double angle = 2 * PI * i / n;

        if(invert)
            angle = -angle;

        complex double w = cos(angle) + I * sin(angle);
        complex double t = w * odd[i];

        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;
    }

    free(even);
    free(odd);
}

int main()
{
    int m, n;
    int size;
    int i;
    complex double *A, *B;

    printf("Enter size of A: ");
    scanf("%d", &m);

    printf("Enter size of B: ");
    scanf("%d", &n);

    size = 1;

    while(size < m + n - 1)
        size = size * 2;

    A = (complex double *)calloc(size, sizeof(complex double));
    B = (complex double *)calloc(size, sizeof(complex double));

    printf("Enter elements of A:\n");

    for(i = 0; i < m; i++)
    {
        double x;
        scanf("%lf", &x);
        A[i] = x;
    }

    printf("Enter elements of B:\n");

    for(i = 0; i < n; i++)
    {
        double x;
        scanf("%lf", &x);
        B[i] = x;
    }

    fft(A, size, 0);
    fft(B, size, 0);

    for(i = 0; i < size; i++)
        A[i] = A[i] * B[i];

    fft(A, size, 1);

    printf("\nConvolution:\n");

    for(i = 0; i < m + n - 1; i++)
    {
        double result = creal(A[i]) / size;

        if(fabs(result) < 0.000001)
            result = 0;

        printf("C[%d] = %.2f\n", i, result);
    }

    free(A);
    free(B);

    return 0;
}