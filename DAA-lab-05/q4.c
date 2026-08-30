#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    int largest;
    int left;
    int right;
    int temp;

    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if(left < n && a[left] > a[largest])
        largest = left;

    if(right < n && a[right] > a[largest])
        largest = right;

    if(largest != i)
    {
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int i, temp;

    /* Build Max Heap */

    for(i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Heap Sort */

    for(i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main()
{
    int a[1000];
    int n, i;

    FILE *fp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    srand((unsigned)time(NULL));

    /* Generate random elements and store in file */

    fp = fopen("input_heap.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    printf("\nRandom elements stored in input_heap.txt\n");

    /* Read elements from file */

    fp = fopen("input_heap.txt", "r");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    for(i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    printf("\nElements before sorting:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    heapSort(a, n);

    printf("\n\nElements after Heap Sort:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}