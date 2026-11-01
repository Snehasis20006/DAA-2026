
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int adj[MAX][MAX];
int degree[MAX];

int owner[MAX];
int distance[MAX];

int queue[MAX];

void addEdge(int u, int v)
{
    adj[u][degree[u]++] = v;
    adj[v][degree[v]++] = u;
}

void multiSourceBFS(int n, int k, int hubs[], int R)
{
    int front = 0;
    int rear = 0;

    int i, v, u;

    // Initialize all vertices as unvisited
    for (i = 1; i <= n; i++)
    {
        owner[i] = -1;
        distance[i] = -1;
    }

    // Insert all hubs into the queue
    for (i = 0; i < k; i++)
    {
        v = hubs[i];

        if (distance[v] == -1 ||
            i + 1 < owner[v])
        {
            distance[v] = 0;
            owner[v] = i + 1;
            queue[rear++] = v;
        }
    }

    // Multi-Source BFS
    while (front < rear)
    {
        u = queue[front++];

        // Do not explore beyond radius R
        if (distance[u] == R)
            continue;

        for (i = 0; i < degree[u]; i++)
        {
            v = adj[u][i];

            if (distance[v] == -1)
            {
                distance[v] = distance[u] + 1;
                owner[v] = owner[u];

                queue[rear++] = v;
            }
            else if (distance[v] == distance[u] + 1 &&
                     owner[u] < owner[v])
            {
                owner[v] = owner[u];
            }
        }
    }

    // Apply radius constraint
    for (i = 1; i <= n; i++)
    {
        if (distance[i] == -1 || distance[i] > R)
        {
            owner[i] = -1;
            distance[i] = -1;
        }
    }
}

int main()
{
    int n, m, k, R;
    int i, u, v;

    int hubs[MAX];

    // Input number of vertices and edges
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    // Initialize adjacency list
    for (i = 1; i <= n; i++)
        degree[i] = 0;

    // Input edges
    printf("Enter the edges (u v):\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);

        addEdge(u, v);
    }

    // Input number of hubs
    printf("Enter number of hubs: ");
    scanf("%d", &k);

    // Input hub vertices
    printf("Enter the hub vertices:\n");

    for (i = 0; i < k; i++)
        scanf("%d", &hubs[i]);

    // Input radius threshold
    printf("Enter radius R: ");
    scanf("%d", &R);

    // Perform Multi-Source BFS
    multiSourceBFS(n, k, hubs, R);

    // Display final ownership and distances
    printf("\nVertex\tOwner\tShortest Distance\n");
    printf("-----------------------------------\n");

    for (i = 1; i <= n; i++)
    {
        printf("%d\t%d\t%d\n",
               i, owner[i], distance[i]);
    }

    return 0;
}
// output-----------------------------------------
//Enter number of vertices: 8
// Enter number of edges: 8
// Enter the edges (u v):
// 1 2
// 2 3
// 3 4
// 4 5 
// 5 6
// 6 7
// 7 8
// 2 5
// Enter number of hubs: 2
// Enter the hub vertices:
// 1 6
// Enter radius R: 2

// Vertex  Owner   Shortest Distance
// -----------------------------------
// 1       1       0
// 2       1       1
// 3       1       2
// 4       2       2
// 5       2       1
// 6       2       0
// 7       2       1
// 8       2       2