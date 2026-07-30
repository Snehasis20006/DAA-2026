#include <stdio.h>
#include <string.h>

struct Function
{
    char name[30];
    int rank;
};

int main()
{
    int i, j;
    struct Function f[] =
    {
        {"nlog2n", 7},
        {"12sqrt(n)", 3},
        {"1/n", 1},
        {"n^(log2n)", 11},
        {"100n^2+6n", 8},
        {"n^0.51", 5},
        {"n^2-324", 9},
        {"50n^0.5", 4},
        {"2n^3", 10},
        {"3^n", 12},
        {"2^32n", 6},
        {"log2n", 2}
    };

    int n = sizeof(f) / sizeof(f[0]);
    struct Function temp;

    // Bubble Sort based on rank
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(f[j].rank > f[j + 1].rank)
            {
                temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }

    printf("Functions in Increasing Order of Growth:\n\n");

    for(i = 0; i < n; i++)
    {
        printf("%2d. %s\n", i + 1, f[i].name);
    }

    return 0;
}