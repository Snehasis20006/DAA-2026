// Question--- Shortest Path on Parity-Constrained Graphs via 0-1 BFS.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

struct Edge {
    int to;
    int weight;
    int next;
};

int main(void) {
    int V, E, source;
    long long C;
    int i, u, v, w;

    printf("Enter vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2 ||
        V <= 0 || E < 0 || E > (INT_MAX - 2 * V - 10) / 4) {
        printf("Invalid input.\n");
        return 1;
    }

    int *head = malloc((V + 1) * sizeof(int));
    struct Edge *edges =
        malloc((E > 0 ? E : 1) * sizeof(struct Edge));

    if (head == NULL || edges == NULL) {
        printf("Memory allocation failed.\n");
        free(head);
        free(edges);
        return 1;
    }

    for (i = 1; i <= V; i++)
        head[i] = -1;

    printf("Enter edges: u v weight\n");

    for (i = 0; i < E; i++) {
        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 1 || u > V || v < 1 || v > V ||
            (w != 0 && w != 1)) {
            printf("Invalid edge.\n");
            free(head);
            free(edges);
            return 1;
        }

        edges[i].to = v;
        edges[i].weight = w;
        edges[i].next = head[u];
        head[u] = i;
    }

    printf("Enter source and penalty C: ");

    if (scanf("%d %lld", &source, &C) != 2 ||
        source < 1 || source > V || C < 0) {
        printf("Invalid source or penalty.\n");
        free(head);
        free(edges);
        return 1;
    }

    int states = 2 * V;
    long long *dist =
        malloc((size_t)states * sizeof(long long));

    int capacity = 4 * E + 2 * V + 10;
    int *deque = malloc((size_t)capacity * sizeof(int));

    if (dist == NULL || deque == NULL) {
        printf("Memory allocation failed.\n");
        free(head);
        free(edges);
        free(dist);
        free(deque);
        return 1;
    }

    for (i = 0; i < states; i++)
        dist[i] = INF;

    /* State 0 = even parity; state 1 = odd parity. */
    int start = 2 * (source - 1);
    int front = 0, back = 0;

    dist[start] = 0;
    deque[back] = start;
    back = (back + 1) % capacity;

    while (front != back) {
        int state = deque[front];
        front = (front + 1) % capacity;

        u = state / 2 + 1;
        int parity = state % 2;

        for (i = head[u]; i != -1; i = edges[i].next) {
            v = edges[i].to;
            w = edges[i].weight;

            int newParity = parity ^ w;
            int nextState = 2 * (v - 1) + newParity;
            long long newDist = dist[state] + w;

            if (newDist < dist[nextState]) {
                dist[nextState] = newDist;

                if (w == 0) {
                    front = (front - 1 + capacity) % capacity;
                    deque[front] = nextState;
                } else {
                    deque[back] = nextState;
                    back = (back + 1) % capacity;
                }
            }
        }
    }

    printf("\nMinimum effective costs:\n");

    for (v = 1; v <= V; v++) {
        int evenState = 2 * (v - 1);
        int oddState = evenState + 1;

        long long evenCost = dist[evenState];
        long long oddCost = INF;

        if (dist[oddState] != INF)
            oddCost = dist[oddState] + C;

        if (evenCost == INF && oddCost == INF) {
            printf("Vertex %d: Unreachable\n", v);
        } else {
            long long answer =
                (evenCost < oddCost) ? evenCost : oddCost;

            printf("Vertex %d: %lld\n", v, answer);
        }
    }

    free(head);
    free(edges);
    free(dist);
    free(deque);

    return 0;
}
