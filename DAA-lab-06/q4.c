#include <stdio.h>

#define MAX 1000

long long totalCost = 0;
int totalReversals = 0;

/* Reverse elements from l to r-1 */
void reverseRange(int a[], int l, int r)
{
    int i = l;
    int j = r - 1;
    int temp;

    if(l >= r)
        return;

    totalCost += (r - l);
    totalReversals++;

    while(i < j)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}

/* First position containing value >= x */
int lowerBound(int a[], int l, int r, int x)
{
    int low = l;
    int high = r;
    int mid;

    while(low < high)
    {
        mid = (low + high) / 2;

        if(a[mid] < x)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/* First position containing value > x */
int upperBound(int a[], int l, int r, int x)
{
    int low = l;
    int high = r;
    int mid;

    while(low < high)
    {
        mid = (low + high) / 2;

        if(a[mid] <= x)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/*
   Merge two sorted ranges:

   [first ... middle-1]
   [middle ... last-1]
*/
void mergeInPlace(int a[], int first, int middle, int last)
{
    int firstCut;
    int secondCut;
    int newMiddle;
    int n1, n2;

    if(first >= middle || middle >= last)
        return;

    /* Two elements */
    if(last - first == 2)
    {
        if(a[middle] < a[first])
            reverseRange(a, first, last);

        return;
    }

    n1 = middle - first;
    n2 = last - middle;

    if(n1 > n2)
    {
        firstCut = first + n1 / 2;

        secondCut = lowerBound(
            a,
            middle,
            last,
            a[firstCut]
        );
    }
    else
    {
        secondCut = middle + n2 / 2;

        if(secondCut == last)
        {
            firstCut = middle;
        }
        else
        {
            firstCut = upperBound(
                a,
                first,
                middle,
                a[secondCut]
            );
        }
    }

    /*
       Rotate:

       A B

       into

       B A

       using three reversals.
    */

    newMiddle = firstCut + (secondCut - middle);

    reverseRange(a, firstCut, middle);
    reverseRange(a, middle, secondCut);
    reverseRange(a, firstCut, secondCut);

    /* Merge left part */
    mergeInPlace(
        a,
        first,
        firstCut,
        newMiddle
    );

    /* Merge right part */
    mergeInPlace(
        a,
        newMiddle,
        secondCut,
        last
    );
}

/* Reversal based merge sort */
void reversalMergeSort(int a[], int left, int right)
{
    int mid;

    if(right - left <= 1)
        return;

    mid = (left + right) / 2;

    reversalMergeSort(a, left, mid);
    reversalMergeSort(a, mid, right);

    mergeInPlace(a, left, mid, right);
}

int main()
{
    int a[MAX];
    int n;
    int i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter permutation:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    reversalMergeSort(a, 0, n);

    printf("\nSorted permutation:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    printf("\nTotal reversals = %d\n", totalReversals);
    printf("Total reversal cost = %lld\n", totalCost);

    printf("\nTheoretical cost = O(n log^2 n)\n");

    return 0;
}