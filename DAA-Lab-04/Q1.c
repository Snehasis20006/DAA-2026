#include <stdio.h>
#include <string.h>

struct Item
{
    int number;
    char color[10];
};

int main()
{
    int n, i;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item a[100];
    struct Item red[100], blue[100], yellow[100];

    int r = 0, b = 0, y = 0;
      
    for(i = 0; i < n; i++)
    {
        scanf("%d %s", &a[i].number, a[i].color);

        if(strcmp(a[i].color, "red") == 0){
            red[r] = a[i];
            r++;
        }
        else if(strcmp(a[i].color, "blue") == 0)
            blue[b++] = a[i];
        else
            yellow[y++] = a[i];
    }

    printf("\nSorted by Color:\n");

    for(i = 0; i < r; i++)
        printf("%d %s\n", red[i].number, red[i].color);

    for(i = 0; i < b; i++)
        printf("%d %s\n", blue[i].number, blue[i].color);

    for(i = 0; i < y; i++)
        printf("%d %s\n", yellow[i].number, yellow[i].color);

    return 0;
}
