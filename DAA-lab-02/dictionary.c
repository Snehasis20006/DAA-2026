#include <stdio.h>
#include<stdlib.h>

#define MAX 100

/* Structure for singly linked list */
struct SNode
{
    int data;
    struct SNode *next;
};

/* Structure for doubly linked list */
struct DNode
{
    int data;
    struct DNode *prev;
    struct DNode *next;
};


/* -------------------------------------------------- */
/* Function to display complexity table               */
/* -------------------------------------------------- */

void displayTable()
{
    printf("\n\n");
    printf("==========================================================================\n");
    printf("                     DICTIONARY OPERATIONS                               \n");
    printf("==========================================================================\n");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Data Structure", "Search", "Insert", "Delete",
           "Min", "Max", "Pred", "Succ");

    printf("--------------------------------------------------------------------------\n");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Unsorted Array",
           "O(n)", "O(n)", "O(n)", "O(n)", "O(n)", "O(n)", "O(n)");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Sorted Array",
           "O(logn)", "O(n)", "O(n)", "O(1)", "O(1)", "O(1)", "O(1)");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Singly Linked Unsorted",
           "O(n)", "O(1)", "O(n)", "O(n)", "O(n)", "O(n)", "O(n)");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Singly Linked Sorted",
           "O(n)", "O(n)", "O(n)", "O(1)", "O(n)", "O(n)", "O(n)");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Doubly Linked Unsorted",
           "O(n)", "O(1)", "O(1)", "O(n)", "O(n)", "O(n)", "O(n)");

    printf("%-30s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n",
           "Doubly Linked Sorted",
           "O(n)", "O(n)", "O(n)", "O(1)", "O(n)", "O(n)", "O(n)");

    printf("==========================================================================\n");
}


/* -------------------------------------------------- */
/* Sorting function for sorted array                  */
/* -------------------------------------------------- */

void sortArray(int a[], int n)
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}


/* -------------------------------------------------- */
/* Create singly linked list                          */
/* -------------------------------------------------- */

struct SNode* createSingly(int a[], int n)
{
    struct SNode *head, *temp, *newnode;
    int i;

    head = NULL;

    for(i = 0; i < n; i++)
    {
        newnode = (struct SNode*)malloc(sizeof(struct SNode));

        newnode->data = a[i];
        newnode->next = NULL;

        if(head == NULL)
        {
            head = newnode;
        }
        else
        {
            temp = head;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
        }
    }

    return head;
}


/* -------------------------------------------------- */
/* Create doubly linked list                          */
/* -------------------------------------------------- */

struct DNode* createDoubly(int a[], int n)
{
    struct DNode *head, *temp, *newnode;
    int i;

    head = NULL;
    temp = NULL;

    for(i = 0; i < n; i++)
    {
        newnode = (struct DNode*)malloc(sizeof(struct DNode));

        newnode->data = a[i];
        newnode->next = NULL;
        newnode->prev = temp;

        if(head == NULL)
            head = newnode;
        else
            temp->next = newnode;

        temp = newnode;
    }

    return head;
}


/* -------------------------------------------------- */
/* Display singly linked list                         */
/* -------------------------------------------------- */

void displaySingly(struct SNode *head)
{
    struct SNode *temp;

    temp = head;

    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}


/* -------------------------------------------------- */
/* Display doubly linked list                         */
/* -------------------------------------------------- */

void displayDoubly(struct DNode *head)
{
    struct DNode *temp;

    temp = head;

    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}


/* -------------------------------------------------- */
/* ASCII Order of Growth Graph                        */
/* -------------------------------------------------- */

void displayGraph()
{
    int n;
    int i;

    printf("\n\n");
    printf("ORDER OF GROWTH GRAPH\n");
    printf("=====================\n\n");

    printf("The graph below represents increasing input size.\n\n");

    printf("O(1)       : ");
    for(i = 0; i < 5; i++)
        printf("*");
    printf("\n");

    printf("O(log n)   : ");
    for(i = 0; i < 15; i++)
        printf("*");
    printf("\n");

    printf("O(n)       : ");
    for(i = 0; i < 40; i++)
        printf("*");
    printf("\n");

    printf("O(n log n) : ");
    for(i = 0; i < 60; i++)
        printf("*");
    printf("\n");

    printf("O(n^2)     : ");
    for(i = 0; i < 75; i++)
        printf("*");
    printf("\n\n");

    printf("Growth rate:\n");
    printf("O(1) < O(log n) < O(n) < O(n log n) < O(n^2)\n");
}


/* -------------------------------------------------- */
/* Main Function                                      */
/* -------------------------------------------------- */

int main()
{
    int a[MAX];
    int sorted[MAX];

    struct SNode *singlyUnsorted;
    struct SNode *singlySorted;

    struct DNode *doublyUnsorted;
    struct DNode *doublySorted;

    int n;
    int i;

    printf("============================================\n");
    printf("       DICTIONARY DATA STRUCTURES\n");
    printf("============================================\n");

    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    if(n <= 0 || n > MAX)
    {
        printf("Invalid size. Enter size between 1 and %d.\n", MAX);
        return 0;
    }

    printf("\nEnter %d elements:\n", n);

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        sorted[i] = a[i];
    }

    /* Sort copy of array */
    sortArray(sorted, n);

    /* Create linked lists */
    singlyUnsorted = createSingly(a, n);
    singlySorted = createSingly(sorted, n);

    doublyUnsorted = createDoubly(a, n);
    doublySorted = createDoubly(sorted, n);

    /* Display input */
    printf("\n\nUnsorted Array:\n");

    for(i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n\nSorted Array:\n");

    for(i = 0; i < n; i++)
        printf("%d ", sorted[i]);

    printf("\n\nSingly Linked Unsorted List:\n");
    displaySingly(singlyUnsorted);

    printf("\n\nSingly Linked Sorted List:\n");
    displaySingly(singlySorted);

    printf("\n\nDoubly Linked Unsorted List:\n");
    displayDoubly(doublyUnsorted);

    printf("\n\nDoubly Linked Sorted List:\n");
    displayDoubly(doublySorted);

    /* Display complexity table */
    displayTable();

    /* Display graph */
    displayGraph();

    printf("\n\nCONCLUSION\n");
    printf("==========\n");
    printf("Different data structures provide different running times.\n");
    printf("Sorted structures make Min and Max easier to obtain.\n");
    printf("Linked lists allow insertion/deletion without shifting elements.\n");
    printf("The asymptotic complexity depends on the structure used.\n");

    return 0;
}