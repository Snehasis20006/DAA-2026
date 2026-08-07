




#include <stdio.h>

void merge(int a[], int n1, int b[], int n2, int c[])
{
    int i = 0, j = 0, k = 0;

    while(i < n1 && j < n2)
    {
        if(a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }

    while(i < n1)
        c[k++] = a[i++];

    while(j < n2)
        c[k++] = b[j++];
}

int main()
{
    int k, n;
    int i, j, l;
    int newK;

    int arrays[10][1000];
    int nextArrays[10][1000];
    int size[10];
    int nextSize[10];
    int temp[1000];

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    printf("Enter number of elements in each array: ");
    scanf("%d", &n);

    printf("Enter sorted arrays:\n");

    for(i = 0; i < k; i++)
    {
        size[i] = n;
        for(j = 0; j < n; j++)
            scanf("%d", &arrays[i][j]);
    }

    while(k > 1)
    {
        newK = 0;

        for(i = 0; i < k; i += 2)
        {
            if(i + 1 < k)
            {
                merge(arrays[i], size[i],
                      arrays[i + 1], size[i + 1],
                      temp);

                nextSize[newK] = size[i] + size[i + 1];

                for(j = 0; j < nextSize[newK]; j++)
                    nextArrays[newK][j] = temp[j];
            }
            else
            {
                nextSize[newK] = size[i];

                for(j = 0; j < size[i]; j++)
                    nextArrays[newK][j] = arrays[i][j];
            }

            newK++;
        }

        /* Copy nextArrays back to arrays */
        for(i = 0; i < newK; i++)
        {
            size[i] = nextSize[i];

            for(l = 0; l < size[i]; l++)
                arrays[i][l] = nextArrays[i][l];
        }

        k = newK;
    }

    printf("\nFinal Merged Array:\n");

    for(i = 0; i < size[0]; i++)
        printf("%d ", arrays[0][i]);

    printf("\n");

    return 0;
}