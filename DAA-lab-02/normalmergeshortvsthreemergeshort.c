#include <stdio.h>

/* Count comparisons */
long normalComparisons = 0;
long threeWayComparisons = 0;

/* ---------- NORMAL MERGE SORT ---------- */

void merge(int a[], int low, int mid, int high)
{
    int temp[100];
    int i, j, k;

    i = low;
    j = mid + 1;
    k = low;

    while(i <= mid && j <= high)
    {
        normalComparisons++;

        if(a[i] <= a[j])
        {
            temp[k] = a[i];
            i++;
        }
        else
        {
            temp[k] = a[j];
            j++;
        }

        k++;
    }

    while(i <= mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }

    while(j <= high)
    {
        temp[k] = a[j];
        j++;
        k++;
    }

    for(i = low; i <= high; i++)
        a[i] = temp[i];
}

void mergeSort(int a[], int low, int high)
{
    int mid;

    if(low < high)
    {
        mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}


/* ---------- THREE-WAY MERGE SORT ---------- */

void mergeThree(int a[], int low, int mid1, int mid2, int high)
{
    int temp[100];
    int i, j, k;
    int p, q, r;

    p = low;
    q = mid1 + 1;
    r = mid2 + 1;
    k = low;

    while(p <= mid1 || q <= mid2 || r <= high)
    {
        if(p <= mid1 &&
           (q > mid2 || a[p] <= a[q]) &&
           (r > high || a[p] <= a[r]))
        {
            temp[k] = a[p];
            p++;
        }
        else if(q <= mid2 &&
                (r > high || a[q] <= a[r]))
        {
            temp[k] = a[q];
            q++;
        }
        else
        {
            temp[k] = a[r];
            r++;
        }

        threeWayComparisons++;
        k++;
    }

    for(i = low; i <= high; i++)
        a[i] = temp[i];
}

void threeWayMergeSort(int a[], int low, int high)
{
    int third;
    int mid1, mid2;

    if(low < high)
    {
        third = (high - low + 1) / 3;

        mid1 = low + third - 1;
        mid2 = low + 2 * third - 1;

        /* If array is too small for 3 parts */
        if(third == 0)
        {
            mid1 = low;
            mid2 = low;
        }

        threeWayMergeSort(a, low, mid1);

        if(mid1 + 1 <= mid2)
            threeWayMergeSort(a, mid1 + 1, mid2);

        if(mid2 + 1 <= high)
            threeWayMergeSort(a, mid2 + 1, high);

        mergeThree(a, low, mid1, mid2, high);
    }
}


/* ---------- MAIN ---------- */

int main()
{
    int a[100], b[100];
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    /* Normal Merge Sort */
    normalComparisons = 0;
    mergeSort(a, 0, n - 1);

    /* Modified 3-Way Merge Sort */
    threeWayComparisons = 0;
    threeWayMergeSort(b, 0, n - 1);

    printf("\nSorted array using Normal Merge Sort:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    printf("\nSorted array using 3-Way Merge Sort:\n");

    for(i = 0; i < n; i++)
        printf("%d ", b[i]);

    printf("\n");

    printf("\nNumber of comparisons:\n");
    printf("Normal Merge Sort   = %ld\n", normalComparisons);
    printf("3-Way Merge Sort    = %ld\n", threeWayComparisons);

    printf("\nWorst-case order of growth:\n");
    printf("Normal Merge Sort   = O(n log n)\n");
    printf("3-Way Merge Sort    = O(n log n)\n");

    return 0;
}